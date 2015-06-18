#include "Ccd.h"

namespace cor3d {
    Ccd::Ccd(BaseEntityCollection& joints, vector<DCoordinate3>& initialJointAbsoulteCoordinates, vector<DCoordinate3>& currentJointAbsoulteCoordinates) :
            Algorithm(joints, initialJointAbsoulteCoordinates, currentJointAbsoulteCoordinates)
    {
    }

    bool Ccd::specificMoveToTarget(const DCoordinate3 target)
    {
        if (_chains.size() > 1)
        {
            return false;
        }
        ccdAlgorithm(_chains[0], target, 1e-10);
    }


    void Ccd::ccdAlgorithm(Chain& chain, DCoordinate3 target, double tolerance)
    {
        cout << "ccd van" << endl;

        unsigned int chainSize = chain.get_chain_size();
        double previousLinkLength = 0.0;
        for (unsigned int i = chainSize - 2; i > 0; i--)
        {
            DCoordinate3 currentToTargetVector = DCoordinate3(target);
            currentToTargetVector -= chain.get_joint_coordinates(i);

            DCoordinate3 currentToNextVector = DCoordinate3(chain.get_joint_coordinates(i + 1));
            currentToNextVector -= chain.get_joint_coordinates(i);

            double angleCos = (currentToTargetVector * currentToNextVector) / (currentToTargetVector.length() * currentToNextVector.length());
            double angleSin = (currentToTargetVector ^ currentToNextVector).length() / (currentToTargetVector.length() * currentToNextVector.length());

            DCoordinate3 rotateAround = currentToNextVector ^ currentToTargetVector;


            Matrix<double> inputMat = Matrix<double>(4, 1);
            inputMat(0, 0) = currentToNextVector.x();
            inputMat(1, 0) = currentToNextVector.y();
            inputMat(2, 0) = currentToNextVector.z();
            inputMat(3, 0) = 1.0;

            ArbitraryAxisRotationMatrix rotationMat = ArbitraryAxisRotationMatrix(rotateAround.x(), rotateAround.y(), rotateAround.z(), angleSin, angleCos);


            Matrix<double> result = rotationMat * inputMat;
            cout << result << endl << endl;
            chain.set_joint_coordinates(chain.get_joint_coordinates(i) + DCoordinate3(result(0, 0), result(1, 0), result(2, 0)),i + 1);



            cout << angleCos << " " << angleSin << endl;
            cout << currentToTargetVector << endl;
            cout << currentToNextVector << endl;
            cout << (currentToNextVector ^ currentToTargetVector) << endl;

            break;
        }
        cout << endl << endl << endl << endl;

        /*
        double *lengths = new double[chain.get_chain_size()];
        double total_length = 0.0;
        for (int i = 0; i < chain.get_chain_size() - 1; i++)
        {
            lengths[i] = (chain.get_joint_coordinates(i) - chain.get_joint_coordinates(i + 1)).length();
            total_length += lengths[i];
        }
        double distance = (target - chain.get_joint_coordinates(chain.get_chain_size() - 1)).length();
        if (distance > total_length)
        {
            for (int i = 0; i < chain.get_chain_size() - 1; i++)
            {
                double r = (target - chain.get_joint_coordinates(i)).length();
                double lambda = lengths[i] / r;

                // innen folytatni
                chain.set_joint_coordinates(DCoordinate3((1 - lambda) * chain.get_joint_coordinates(i) + lambda * target), i + 1);
            }
        }
        else
        {
            DCoordinate3 b = DCoordinate3(chain.get_joint_coordinates(0));
            double dif_A = (target - chain.get_joint_coordinates(chain.get_chain_size() - 1)).length();
            unsigned int iteration_count = 0, max_iteration = 10;
            while (dif_A > tolerance && iteration_count < max_iteration)
            {
                iteration_count++;
                chain.set_joint_coordinates(DCoordinate3(target), chain.get_chain_size() - 1);
                for (int i = chain.get_chain_size() - 2; i >= 0; i--)
                {
                    double r = (chain.get_joint_coordinates(i + 1) - chain.get_joint_coordinates(i)).length();
                    double lambda = lengths[i] / r;
                    chain.set_joint_coordinates((1 - lambda) * chain.get_joint_coordinates(i + 1) + lambda * chain.get_joint_coordinates(i), i);
                }
                chain.set_joint_coordinates(b, 0);
                for (int i = 0; i < chain.get_chain_size() - 1; i++)
                {
                    double r = (chain.get_joint_coordinates(i + 1) - chain.get_joint_coordinates(i)).length();
                    double lambda = lengths[i] / r;
                    chain.set_joint_coordinates( DCoordinate3((1 - lambda) * chain.get_joint_coordinates(i) + lambda * chain.get_joint_coordinates(i + 1)), i + 1);
                }
                dif_A = (target - chain.get_joint_coordinates(chain.get_chain_size() - 1)).length();
            }
        }
        */
    }
}

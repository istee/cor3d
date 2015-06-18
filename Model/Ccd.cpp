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

            /*
            double d = sqrt(rotateAround.x() * rotateAround.x() + rotateAround.y() * rotateAround.y() + rotateAround.z() * rotateAround.z());

            Matrix<double> identity = Matrix<double>(3, 3);
            identity(0, 0) = 1;
            identity(1, 1) = 1;
            identity(2, 2) = 1;

            Matrix<double> L = Matrix<double>(3, 3);
            L(0, 1) = rotateAround.z();
            L(0, 2) = -rotateAround.y();
            L(1, 0) = -rotateAround.z();
            L(1, 2) = rotateAround.x();
            L(2, 0) = rotateAround.y();
            L(2, 1) = -rotateAround.x();
            */

            //DCoordinate3 result = currentToNextVector ^ (identity + angleSin / d * L + ((1 - angleCos) / (d * d) * (L ^ L)));



            float rotationMatrix[4][4];
            float inputMatrix[4][1] = {0.0, 0.0, 0.0, 0.0};
            float outputMatrix[4][1] = {0.0, 0.0, 0.0, 0.0};

            inputMatrix[0][0] = currentToNextVector.x();
                inputMatrix[1][0] = currentToNextVector.y();
                inputMatrix[2][0] = currentToNextVector.z();
                inputMatrix[3][0] = 1.0;

                double u = rotateAround.x();
                double v = rotateAround.y();
                double w = rotateAround.z();


            float L = (u*u + v * v + w * w);
                //angle = angle * M_PI / 180.0; //converting to radian value
                float u2 = u * u;
                float v2 = v * v;
                float w2 = w * w;

                rotationMatrix[0][0] = (u2 + (v2 + w2) * angleCos) / L;
                rotationMatrix[0][1] = (u * v * (1 - angleCos) - w * sqrt(L) * angleSin) / L;
                rotationMatrix[0][2] = (u * w * (1 - angleCos) + v * sqrt(L) * angleSin) / L;
                rotationMatrix[0][3] = 0.0;

                rotationMatrix[1][0] = (u * v * (1 - angleCos) + w * sqrt(L) * angleSin) / L;
                rotationMatrix[1][1] = (v2 + (u2 + w2) * angleCos) / L;
                rotationMatrix[1][2] = (v * w * (1 - angleCos) - u * sqrt(L) * angleSin) / L;
                rotationMatrix[1][3] = 0.0;

                rotationMatrix[2][0] = (u * w * (1 - angleCos) - v * sqrt(L) * angleSin) / L;
                rotationMatrix[2][1] = (v * w * (1 - angleCos) + u * sqrt(L) * angleSin) / L;
                rotationMatrix[2][2] = (w2 + (u2 + v2) * angleCos) / L;
                rotationMatrix[2][3] = 0.0;

                rotationMatrix[3][0] = 0.0;
                rotationMatrix[3][1] = 0.0;
                rotationMatrix[3][2] = 0.0;
                rotationMatrix[3][3] = 1.0;

                for(int i = 0; i < 4; i++ ){
                        for(int j = 0; j < 1; j++){
                            outputMatrix[i][j] = 0;
                            for(int k = 0; k < 4; k++){
                                outputMatrix[i][j] += rotationMatrix[i][k] * inputMatrix[k][j];
                            }
                        }
                    }
            chain.set_joint_coordinates(chain.get_joint_coordinates(i) + DCoordinate3(outputMatrix[0][0], outputMatrix[1][0],outputMatrix[2][0]),i + 1);








            cout << angleCos << " " << angleSin << endl;
            cout << currentToTargetVector << endl;
            cout << currentToNextVector << endl;
            cout << (currentToNextVector ^ currentToTargetVector) << endl;
            //cout << result << endl;

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

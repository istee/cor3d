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

        Matrix<double> inputMat = Matrix<double>(4, 1);
        Matrix<double> result = Matrix<double>(1, 4);
        inputMat(3, 0) = 1.0;

        unsigned int chainSize = chain.get_chain_size();
        double dif = (target - chain.get_joint_coordinates(chain.get_chain_size() - 1)).length(), dif_A = 0;
        unsigned int iterationCount = 0, maxIteration = 10;
        while (dif > tolerance && maxIteration > iterationCount)
        {
            for (int i = chainSize - 2; i >= 0; i--)
            {
                DCoordinate3 currentToTargetVector = DCoordinate3(target);
                currentToTargetVector -= chain.get_joint_coordinates(i);

                DCoordinate3 currentToNextVector = DCoordinate3(chain.get_joint_coordinates(chainSize - 1));
                currentToNextVector -= chain.get_joint_coordinates(i);

                double angleCos = (currentToTargetVector * currentToNextVector) / (currentToTargetVector.length() * currentToNextVector.length());
                double angleSin = (currentToTargetVector ^ currentToNextVector).length() / (currentToTargetVector.length() * currentToNextVector.length());

                DCoordinate3 rotateAround = currentToNextVector ^ currentToTargetVector;

                ArbitraryAxisRotationMatrix rotationMat = ArbitraryAxisRotationMatrix(rotateAround.x(), rotateAround.y(), rotateAround.z(), angleSin, angleCos);

                currentToNextVector = DCoordinate3(chain.get_joint_coordinates(i + 1));
                currentToNextVector -= chain.get_joint_coordinates(i);

                for (int j = i; j <= chainSize - 2; j++)
                {
                    inputMat(0, 0) = currentToNextVector.x();
                    inputMat(1, 0) = currentToNextVector.y();
                    inputMat(2, 0) = currentToNextVector.z();

                    result = rotationMat * inputMat;

                    if (j < chainSize - 2)
                    {
                        currentToNextVector = DCoordinate3(chain.get_joint_coordinates(j + 2));
                        currentToNextVector -= chain.get_joint_coordinates(j + 1);
                    }

                    chain.set_joint_coordinates(chain.get_joint_coordinates(j) + DCoordinate3(result(0, 0), result(1, 0), result(2, 0)),j + 1);
                }
            }

            dif_A = dif;
            dif = (target - chain.get_joint_coordinates(chain.get_chain_size() - 1)).length();
            dif_A -= dif;
            cout << "difA " << dif_A << endl;
            iterationCount++;
        }
    }
}

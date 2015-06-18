#include "Fabrik.h"

#include <QtConcurrentMap>

namespace cor3d {
    Fabrik::Fabrik(BaseEntityCollection& joints, vector<DCoordinate3>& initialJointAbsoulteCoordinates, vector<DCoordinate3>& currentJointAbsoulteCoordinates) :
            Algorithm(joints, initialJointAbsoulteCoordinates, currentJointAbsoulteCoordinates)
    {
    }

    void Fabrik::parallelProcessFabrik(double tolerance)
    {
        bool allChainsProcessed = false;
        unsigned int chainLevel = 1;
        QList<FabrikChain> fabrikChainList;
        while (!allChainsProcessed)
        {
            for (unsigned int i = 1; i < _chains.size(); i++)
            {
                if (_chains[i].getChainHierarchyLevel() == chainLevel)
                {
                    fabrikChainList.append(FabrikChain(&_chains[i], _chains[_chains[i].getChainParent()].get_chain_ending(), tolerance));
                }
            }

            if (fabrikChainList.size() == 0)
            {
                allChainsProcessed = true;
            }

            QtConcurrent::blockingMap(fabrikChainList, &FabrikChain::simpleForwardFabrik);

            fabrikChainList.clear();

            chainLevel++;
        }
    }

    bool Fabrik::specificMoveToTarget(const DCoordinate3 target)
    {
        fabrik(_chains[0], target, 1e-10);

        if (!_parallelProcessingEnabled)
        {
            cout << "parallel" << endl;
            parallelProcessFabrik(1e-10);
        }
        else
        {
            cout << "sequential" << endl;
            for (unsigned int i = 1; i < _chains.size(); i++)
            {
                FabrikChain fabrikChain = FabrikChain(&_chains[i], _chains[_chains[i].getChainParent()].get_chain_ending(), 1e-10);
                fabrikChain.simpleForwardFabrik();
            }
        }

        return true;
    }


    void Fabrik::fabrik(Chain& chain, DCoordinate3 target, double tolerance)
    {
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
    }

    void Fabrik::FabrikChain::simpleForwardFabrik()
    {
        double *lengths = new double[_chain->get_chain_size()];
        for (int i = 0; i < _chain->get_chain_size() - 1; i++)
        {
            lengths[i] = (_chain->get_joint_coordinates(i) - _chain->get_joint_coordinates(i + 1)).length();
        }

        _chain->set_joint_coordinates(DCoordinate3(_target), _chain->get_chain_size() - 1);
        for (int i = _chain->get_chain_size() - 2; i >= 0; i--)
        {
            double r = (_chain->get_joint_coordinates(i + 1) - _chain->get_joint_coordinates(i)).length();
            double lambda = lengths[i] / r;
            _chain->set_joint_coordinates(DCoordinate3((1 - lambda) * _chain->get_joint_coordinates(i + 1) + lambda * _chain->get_joint_coordinates(i)), i);
        }

        DCoordinate3 offset = _chain->get_chain_start() - _target;
        for (int i = 0; i < _chain->get_chain_size(); i++)
        {
            _chain->set_joint_coordinates(DCoordinate3(_chain->get_joint_coordinates(i) - offset), i);
        }
    }

    Fabrik::FabrikChain::FabrikChain(Chain* chain, DCoordinate3 target, double tolerance):_chain(chain), _target(target), _tolerance(tolerance)
    {

    }
}

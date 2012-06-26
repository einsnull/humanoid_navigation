// SVN $HeadURL$
// SVN $Id$

/*
 * A footstep planner for humanoid robots
 *
 * Copyright 2010-2011 Johannes Garimort, Armin Hornung, University of Freiburg
 * http://www.ros.org/wiki/footstep_planner
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FOOTSTEP_PLANNER_PATHCOSTHEURISTIC_H_
#define FOOTSTEP_PLANNER_PATHCOSTHEURISTIC_H_

#include <footstep_planner/Heuristic.h>
#include <gridmap_2d/GridMap2D.h>
#include <sbpl/headers.h>


namespace footstep_planner
{
    /**
     * @brief Determining the heuristic value by calculating a 2D path from each
     * grid cell of the map to the goal and using the path length as expected
     * distance.
     *
     * The heuristic value consists of the following factors:
     *
     *  + The expected distance retreived from the 2D path.
     *
     *  + The expected path costs.
     *
     *  + The difference between the orientation of the two states multiplied
     *    by some cost factor.
     */
    class PathCostHeuristic : public Heuristic
    {
    public:
        PathCostHeuristic(double cell_size, int num_angle_bins,
                          double step_cost, double diff_angle_cost,
                          double max_step_width);
        virtual ~PathCostHeuristic();

        virtual double getHValue(const PlanningState& from,
		                         const PlanningState& to) const;

        /**
         * @brief Calculates for each grid cell of the map a 2D path to the
         * goal. (The start state is not really needed here.)
         */
        bool calculateDistances(const PlanningState& start,
                                const PlanningState& goal);

        void updateMap(GridMap2DPtr map);

    private:
        static const int cvObstacleThreshold = 200;

        unsigned char** ivpGrid;

        double ivStepCost;
        double ivDiffAngleCost;
        double ivMaxStepWidth;

        boost::shared_ptr<GridMap2D> ivMapPtr;
        boost::shared_ptr<SBPL2DGridSearch> ivGridSearchPtr;

        void resetGrid();
    };
}
#endif  // FOOTSTEP_PLANNER_PATHCOSTHEURISTIC_H_

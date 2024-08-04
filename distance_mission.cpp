#include <header.hpp>

distance_mission(int mission_id, long int start_mission, long int end_misison, int reward_mission, int target)
    : Mission(mission_id, start_mission, end_misison, reward_mission)
{
    target_distance_in_meters = target;
    have_done = 0;
}
void check_complete(long int start, long int end, int distance)
{
    if (complete || start < start_timestamp || end > end_timestamp)
        return;
    have_done = have_done + distance;
    if (have_done >= target_distance_in_meters)
    {
        complete = true;
        end_timestamp = end;
        // print
    }
}
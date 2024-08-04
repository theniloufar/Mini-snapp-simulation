#include <header.hpp>

time_mission(int mission_id, long int start_mission, long int end_misison, int reward_mission, int target)
    : Mission(mission_id, start_mission, end_misison, reward_mission)
{
    target_time_in_minutes = target;
    have_done = 0;
}
void time_mission check_complete(long int start, long int end, int distance)
{
    if (complete || start < start_timestamp || end > end_timestamp)
        return;
    have_done = have_done + end - start;
    if (have_done >= target_time_in_minutes * 60)
    {
        complete = true;
        end_timestamp = end;
        // print
    }
}
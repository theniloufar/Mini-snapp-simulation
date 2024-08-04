#include <header.hpp>

Mission(int id, long int start, long int end, int reward);
Mission::Mission() {}
int Mission::get_mission_id()
{
    return mission_id;
}
void Mission::check_complete(long int start, long int end, int distance) {}
bool Mission::is_completed()
{
    return complete;
}
#include <header.hpp>

int Driver::get_driver_id()
{
    return driver_id;
}
void Driver::check_mission(long int start, long int end, int distance)
{
    for (int i = 0; i < driver_missions.size(); i++)
    {
        driver_missions[i]->check_complete(start, end, distance);
    }
}
void Driver::add_mission(Mission *mission)
{
    driver_missions.push_back(mission);
    for (int i = 0; i < driver_missions.size(); i++)
    {
        cout << driver_missions[i]->get_mission_id() << " ";
    }
    cout << "\n";
}
Driver::Driver(int id)
{
    driver_id = id;
}

#include <header.hpp>

void Snapp::add_distance_missions(int mission_id, long int start, long int end, int target, int reward)
{
    if (target > 0 && reward > 0)
    {
        if (end > start)
        {
            if (mission_id_is_correct(mission_id))
            {
                Mission *temp = new distance_mission(mission_id, start, end, reward, target);
                missions.push_back(temp);
            }
        }
        else
        {
            cout << "INVALID_ARGUMENTS\n";
        }
    }
    else
    {
        cout << "INVALID_ARGUMENTS\n";
    }
}
void Snapp::add_time_missions(int mission_id, long int start, long int end, int target, int reward)
{
    if (target > 0 && reward > 0)
    {
        if (end > start)
        {
            if (mission_id_is_correct(mission_id))
            {
                Mission *temp = new time_mission(mission_id, start, end, reward, target);
                missions.push_back(temp);
            }
        }
        else
        {
            cout << "INVALID_ARGUMENTS\n";
        }
    }
    else
    {
        cout << "INVALID_ARGUMENTS\n";
    }
}
void Snapp::add_count_missions(int mission_id, long int start, long int end, int target, int reward)
{
    if (target > 0 && reward > 0)
    {
        if (end > start)
        {
            if (mission_id_is_correct(mission_id))
            {
                Mission *temp = new count_mission(mission_id, start, end, reward, target);
                missions.push_back(temp);
            }
        }
        else
        {
            cout << "INVALID_ARGUMENTS\n";
        }
    }
    else
    {
        cout << "INVALID_ARGUMENTS\n";
    }
}
bool Snapp::mission_id_is_correct(int mission_id)
{
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i]->get_mission_id() == mission_id)
        {
            cout << "DUPLICATE_MISSION_ID\n";
            return false;
        }
    }
    return true;
}
void Snapp::assign_missions(int mission_id, int driver_id)
{
    if (!mission_id_exist(mission_id))
    {
        return;
    }
    if (does_driver_exist(driver_id))
    {
        Driver *driver_temp = find_driver_by_id(driver_id);
        Mission *mission_temp = find_mission_by_id(mission_id);
        driver_temp->add_mission(mission_temp);
    }
    else
    {
        Driver *temp = new Driver(driver_id);
        drivers.push_back(temp);
        Mission *mission_temp = find_mission_by_id(mission_id);
        temp->add_mission(mission_temp);
    }
}
bool Snapp::does_driver_exist(int driver_id)
{
    for (int i = 0; i < drivers.size(); i++)
    {
        if (drivers[i]->get_driver_id() == driver_id)
        {
            return true;
        }
    }
    return false;
}
bool Snapp::mission_id_exist(int mission_id)
{
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i]->get_mission_id() == mission_id)
        {
            return true;
        }
    }
    return false;
}
Mission Snapp::*find_mission_by_id(int mission_id)
{
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i]->get_mission_id() == mission_id)
            return missions[i];
    }
    cout << "MISSION_NOT_FOUND\n";
}
Driver Snapp::*find_driver_by_id(int driver_id)
{
    for (int i = 0; i < drivers.size(); i++)
    {
        if (drivers[i]->get_driver_id() == driver_id)
            return drivers[i];
    }
}
void Snapp::record_rides(long int start, long int end, int driver_id, int distance)
{
    if (does_driver_exist(driver_id))
    {
        Driver *temp = find_driver_by_id(driver_id);
        temp->check_mission(start, end, distance);
    }
}
void Snapp::show_mission_status(long int start, long int end, int driver_id, int reward, int mission_id, vector<Mission *> driver_missions)
{
    if (does_driver_exist(driver_id))
    {
        cout << "missions status for driver" << driver_id << endl;
        for (int j = 0; j < driver_missions.size(); j++)
        {
            cout << "mission" << mission_id << ":" << endl;
            cout << "start timestamp: " << start << endl;
            cout << "end timestamp: " << end << endl;
            cout << "reward: " << reward << endl;
            if (driver_missions[j]->is_completed())
            {
                cout << "completed" << endl;
            }
            else
            {
                cout << "ongoing" << endl;
            }
        }
    }
}
void record_ride(Snapp &snap)
{
    int start, end, driver_id, distance;
    cin >> start >> end >> driver_id >> distance;
    snap.record_rides(start, end, driver_id, distance);
}
void assign_mission(Snapp &snap)
{
    int mission_id, driver_id;
    cin >> mission_id >> driver_id;
    snap.assign_missions(mission_id, driver_id);
}
void add_distance_mission(Snapp &snap)
{
    int mission_id, target_distance_in_meters, reward;
    long int start_time, end_time;
    cin >> mission_id >> start_time >> end_time >> target_distance_in_meters >> reward;
    snap.add_distance_missions(mission_id, start_time, end_time, target_distance_in_meters, reward);
}
void add_count_mission(Snapp &snap)
{
    int mission_id, target_number, reward;
    long int start_time, end_time;
    cin >> mission_id >> start_time >> end_time >> target_number >> reward;
    snap.add_count_missions(mission_id, start_time, end_time, target_number, reward);
}
void add_time_mission(Snapp &snap)
{
    int mission_id, target_time_in_minutes, reward;
    long int start_time, end_time;
    cin >> mission_id >> start_time >> end_time >> target_time_in_minutes >> reward;
    snap.add_count_missions(mission_id, start_time, end_time, target_time_in_minutes, reward);
}
void show_missions_status(Snapp &snap)
{
    int driver_id, reward, mission_id;
    long int start_time, end_time;
    vector<Mission *> driver_missions;
    cin >> driver_id;
    snap.show_mission_status(start_time, end_time, driver_id, reward, mission_id, driver_missions);
}
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Mission
{
protected:
    int mission_id;
    long int start_timestamp;
    long int end_timestamp;
    int reward_amount;
    bool complete;

public:
    Mission(int id, long int start, long int end, int reward);
    Mission() {}
    int get_mission_id()
    {
        return mission_id;
    }
    virtual void check_complete(long int start, long int end, int distance) {}
    bool is_completed()
    {
        return complete;
    }
};

Mission::Mission(int id, long int start, long int end, int reward)
{
    mission_id = id;
    start_timestamp = start;
    end_timestamp = end;
    reward_amount = reward;
    complete = false;
}

class Driver
{
private:
    int driver_id;
    vector<Mission *> driver_missions;

public:
    Driver(int id);
    int get_driver_id()
    {
        return driver_id;
    }

    void check_mission(long int start, long int end, int distance)
    {
        for (int i = 0; i < driver_missions.size(); i++)
        {
            driver_missions[i]->check_complete(start, end, distance);
        }
    }

    void add_mission(Mission *mission)
    {
        driver_missions.push_back(mission);
        for (int i = 0; i < driver_missions.size(); i++)
        {
            cout << driver_missions[i]->get_mission_id() << " ";
        }
        cout << "\n";
    }
};

Driver::Driver(int id)
{
    driver_id = id;
}

class time_mission : public Mission
{
private:
    int target_time_in_minutes;
    int have_done;

public:
    time_mission(int mission_id, long int start_mission, long int end_misison, int reward_mission, int target)
        : Mission(mission_id, start_mission, end_misison, reward_mission)
    {
        target_time_in_minutes = target;
        have_done = 0;
    }
    void check_complete(long int start, long int end, int distance)
    {
        if (complete || start < start_timestamp || end > end_timestamp)
            return;
        have_done = have_done + end - start;
        if (have_done >= target_time_in_minutes * 60)
        {
            complete = true;
            end_timestamp = end;
        }
    }
};

class distance_mission : public Mission
{
private:
    int target_distance_in_meters;
    int have_done;

public:
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
};

class count_mission : public Mission
{
private:
    int target_number;
    int have_done;

public:
    count_mission(int mission_id, long int start_mission, long int end_misison, int reward_mission, int target)
        : Mission(mission_id, start_mission, end_misison, reward_mission)
    {
        target_number = target;
        have_done = 0;
    }
    void check_complete(long int start, long int end, int distance)
    {
        if (complete || start < start_timestamp || end > end_timestamp)
            return;
        have_done = have_done++;
        if (have_done >= target_number)
        {
            complete = true;
            end_timestamp = end;
            // print
        }
    }
};

class Snapp
{
private:
    vector<Driver *> drivers;
    vector<Mission *> missions;

public:
    Snapp() {}

    void add_distance_missions(int mission_id, long int start, long int end, int target, int reward)
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

    void add_time_missions(int mission_id, long int start, long int end, int target, int reward)
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

    void add_count_missions(int mission_id, long int start, long int end, int target, int reward)
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

    bool mission_id_is_correct(int mission_id)
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

    void assign_missions(int mission_id, int driver_id)
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

    bool does_driver_exist(int driver_id)
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

    bool mission_id_exist(int mission_id)
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

    Mission *find_mission_by_id(int mission_id)
    {
        for (int i = 0; i < missions.size(); i++)
        {
            if (missions[i]->get_mission_id() == mission_id)
                return missions[i];
        }
        cout << "MISSION_NOT_FOUND\n";
    }

    Driver *find_driver_by_id(int driver_id)
    {
        for (int i = 0; i < drivers.size(); i++)
        {
            if (drivers[i]->get_driver_id() == driver_id)
                return drivers[i];
        }
    }

    void record_rides(long int start, long int end, int driver_id, int distance)
    {
        if (does_driver_exist(driver_id))
        {
            Driver *temp = find_driver_by_id(driver_id);
            temp->check_mission(start, end, distance);
        }
    }

    void show_mission_status(long int start, long int end, int driver_id, int reward, int mission_id, vector<Mission *> driver_missions)
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
};

void read_order();
void read_order()
{
    Snapp snap;
    while (true)
    {
        string order;
        cin >> order;
        if (order == "add_distance_mission")
            add_distance_mission(snap);
        if (order == "add_count_mission")
            add_count_mission(snap);
        if (order == "add_time_mission")
            add_time_mission(snap);
        if (order == "assign_mission")
            assign_mission(snap);
        if (order == "record_ride")
            record_ride(snap);
        if (order == "show_missions_status")
            show_missions_status(snap);
    }
}

void add_distance_mission(Snapp &snap);
void add_count_mission(Snapp &snap);
void add_time_mission(Snapp &snap);
void assign_mission(Snapp &snap);
void record_ride(Snapp &snap);
void show_missions_status(Snapp &snap);

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

int main()
{
    read_order();
}
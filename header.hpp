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
    int get_mission_id();
    virtual void check_complete(long int start, long int end, int distance) {}
    bool is_completed();
};
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

    void check_mission(long int start, long int end, int distance);
    void add_mission(Mission *mission);
};

Driver::Driver(int id);

class time_mission : public Mission
{
private:
    int target_time_in_minutes;
    int have_done;

public:
    time_mission(int mission_id, long int start_mission, long int end_misison, int reward_mission, int target)
        : Mission(mission_id, start_mission, end_misison, reward_mission);
    void check_complete(long int start, long int end, int distance);
};

class distance_mission : public Mission
{
private:
    int target_distance_in_meters;
    int have_done;

public:
    distance_mission(int mission_id, long int start_mission, long int end_misison, int reward_mission, int target)
        : Mission(mission_id, start_mission, end_misison, reward_mission);
    void check_complete(long int start, long int end, int distance);
};

class count_mission : public Mission
{
private:
    int target_number;
    int have_done;

public:
    count_mission(int mission_id, long int start_mission, long int end_misison, int reward_mission, int target);
        : Mission(mission_id, start_mission, end_misison, reward_mission);
        void check_complete(long int start, long int end, int distance);
};

class Snapp
{
    private:
        vector<Driver *> drivers;
        vector<Mission *> missions;

    public:
        Snapp() {}

        void add_distance_missions(int mission_id, long int start, long int end, int target, int reward);
        void add_time_missions(int mission_id, long int start, long int end, int target, int reward);
        void add_count_missions(int mission_id, long int start, long int end, int target, int reward);
        bool mission_id_is_correct(int mission_id);
        void assign_missions(int mission_id, int driver_id);
        ;
        bool mission_id_exist(int mission_id);
        Mission *find_mission_by_id(int mission_id);
        Driver *find_driver_by_id(int driver_id);
        void record_rides(long int start, long int end, int driver_id, int distance);
        void show_mission_status(long int start, long int end, int driver_id, int reward, int mission_id, vector<Mission *> driver_missions);
};
void read_order();
void add_distance_mission(Snapp &snap);
void add_count_mission(Snapp &snap);
void add_time_mission(Snapp &snap);
void assign_mission(Snapp &snap);
void record_ride(Snapp &snap);
void show_missions_status(Snapp &snap);
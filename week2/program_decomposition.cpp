#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus=0,
    BusesForStop=1,
    StopsForBus=2,
    AllBuses=3
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string t, bus, stop;
    is >> t;
    if (t == "NEW_BUS"){
        q.type = QueryType::NewBus;
        int stop_count=0;
        is >> q.bus >> stop_count;
        q.stops = vector<string>(stop_count);
        for (string& cur_stop : q.stops){
            is >> cur_stop;
        }
    }
    else if (t == "BUSES_FOR_STOP"){
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (t == "STOPS_FOR_BUS"){
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (t == "ALL_BUSES"){
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    bool stop_exists = false;
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.stop_exists){
        for (const string& bus : r.buses){
            os << bus << " ";
        }
    }
    else os << "No stop";
    return os;
}

struct StopsForBusResponse {
    bool bus_exists = false;
    vector<string> stops;
    vector<vector<string>> stops_answers;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.bus_exists){
        for (size_t i = 0; i < r.stops.size(); i++) {
            if (i != 0){
                os << endl;
            }
            os << "Stop " << r.stops[i] << ": ";
            if (r.stops_answers[i].empty()){
                os << "no interchange";
            }
            else {
                for (const string& bus : r.stops_answers[i]){
                    os << bus << " ";
                }
            }
        }
    }
    else os << "No bus";
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> all_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.all_buses.empty()){
        os << "No buses";
    }
    else{
        bool first = true;
        for (const auto& [bus, stops] : r.all_buses){
            if (!first){
                os << endl;
            }
            first = false;
            os << "Bus " << bus << ": ";
            for (const string& stop : stops){
                os << stop << " ";
            }
        }
    }
    return os;
}

class BusManager {
private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stop_to_buses;
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const string& stop : stops){
            stop_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse response;
        response.stop_exists = stop_to_buses.count(stop) != 0;
        if (response.stop_exists){
            response.buses = stop_to_buses.at(stop);
        }
        return response;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse response;
        response.bus_exists = buses_to_stops.count(bus) != 0;
        if (response.bus_exists){
            size_t i = 0;
            response.stops_answers.resize(buses_to_stops.at(bus).size());
            for (const string& stop : buses_to_stops.at(bus)){
                response.stops.push_back(stop);
                for (const string& interchange_bus : stop_to_buses.at(stop)){
                    if (interchange_bus != bus){
                        response.stops_answers[i].push_back(interchange_bus);
                    }
                }
                i++;
            }
        }
        return response;
    }

    AllBusesResponse GetAllBuses() const {
        return {buses_to_stops};
    }
};


int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
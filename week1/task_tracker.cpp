#include "vector"
class TeamTasks {
private:
    std::map<std::string, TasksInfo> stats;
    std::vector<TaskStatus> task_status_vector = {TaskStatus::NEW, TaskStatus::IN_PROGRESS,
                                                  TaskStatus::TESTING, TaskStatus::DONE};
public:
    const TasksInfo& GetPersonTasksInfo(const std::string& person) const{
        return stats.at(person);
    }
    void AddNewTask(const std::string& person){
        stats[person][TaskStatus::NEW]++;
    }
    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count){
        TasksInfo current_info = stats[person];
        TasksInfo updated_info, untouched_info;
        TasksInfo new_state = current_info;

        for (size_t i = 0; i < task_status_vector.size() - 1; i++){
            TaskStatus status = task_status_vector[i];
            TaskStatus next_status = task_status_vector[i + 1];
            if (current_info.count(status) != 0){
                int updated_tasks = std::min(task_count, current_info[status]);
                if (updated_tasks > 0){
                    updated_info[next_status] = updated_tasks;
                    new_state[next_status] += updated_tasks;
                    new_state[status] -= updated_tasks;
                    if (new_state[status] == 0){
                        new_state.erase(status);
                    }
                }
                int remaining_tasks = current_info[status] - updated_tasks;
                if (remaining_tasks > 0){
                    untouched_info[status] = remaining_tasks;
                }
                task_count = std::max(0, task_count - updated_tasks);
            }
        }
        stats[person] = new_state;
        return {updated_info, untouched_info};
    }
};
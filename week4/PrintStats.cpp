void PrintStats(std::vector<Person> people){
    std::cout << "Median age = " <<
              ComputeMedianAge(std::begin(people), std::end(people)) << std::endl;
    auto fem_it = std::partition(std::begin(people), std::end(people),
                                 [](const Person& p){return p.gender == Gender::FEMALE;});
    std::cout << "Median age for females = " <<
              ComputeMedianAge(std::begin(people), fem_it) << std::endl;
    std::cout << "Median age for males = " <<
              ComputeMedianAge(fem_it, std::end(people)) << std::endl;
    auto occup_fem = std::partition(std::begin(people), fem_it,
                                    [](const Person& p) {return p.is_employed;});
    std::cout << "Median age for employed females = " <<
              ComputeMedianAge(std::begin(people), occup_fem) << std::endl;
    std::cout << "Median age for unemployed females = " <<
              ComputeMedianAge(occup_fem, fem_it) << std::endl;
    auto occup_m = std::partition(fem_it, std::end(people),
                                  [](const Person& p) {return p.is_employed;});
    std::cout << "Median age for employed males = " <<
              ComputeMedianAge(fem_it, occup_m) << std::endl;
    std::cout << "Median age for unemployed males = " <<
              ComputeMedianAge(occup_m, std::end(people));
}
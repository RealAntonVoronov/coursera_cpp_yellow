std::tuple<const std::string&, const std::string&,
        const std::map<Lang, std::string>&, const int64_t&> MakeTuple(const Region& region) {
    return {region.std_name, region.parent_std_name, region.names, region.population};
}
int FindMaxRepetitionCount(const std::vector<Region>& regions){
    std::map<std::tuple<const std::string&, const std::string&,
            const std::map<Lang, std::string>&, const int64_t&>, int> counts;
    for (const Region& region : regions) {
        counts[MakeTuple(region)]++;
    }
    int res = 0;
    for (const auto& x : counts){
        if (x.second > res){
            res = x.second;
        }
    }
    return res;
}
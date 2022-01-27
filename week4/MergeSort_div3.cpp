template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    RandomIt border_1 = std::begin(elements) + elements.size() / 3;
    RandomIt border_2 = std::begin(elements) + 2 * elements.size() / 3;
    MergeSort(std::begin(elements), border_1);
    MergeSort(border_1, border_2);
    MergeSort(border_2, std::end(elements));
    vector<typename RandomIt::value_type> temp;
    std::merge(std::begin(elements), border_1, border_1, border_2, std::back_inserter(temp));
    std::merge(std::begin(temp), std::end(temp), border_2, std::end(elements), range_begin);
}
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    RandomIt middle = std::begin(elements) + elements.size() / 2;
    MergeSort(std::begin(elements), middle);
    MergeSort(middle, std::end(elements));
    std::merge(std::begin(elements), middle, middle, std::end(elements), range_begin);
}
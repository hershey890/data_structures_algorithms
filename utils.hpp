template<typename T>
void printBinary(const T num) {
    const size_t n = sizeof(T)*8;
    string res(n, ' ');
    for(size_t i=0; i<n; i++) {
        unsigned char tmp = ((num & (1UL << i)) >> i);
        assert(tmp == 0 || tmp == 1);
        res[n-i-1] = tmp + '0';
    }
    cout << res << endl;
}

template<typename T>
void printContainer(T container) {
    size_t n = container.size();
    while(n--) {
        cout << container[i] << " ";
        container.pop_front();
    }
    cout << endl;
}
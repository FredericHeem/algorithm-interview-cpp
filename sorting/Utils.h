
template<class T>
bool isSorted(T container){
    for(auto it = container.begin(); it < container.end(); ++it){
        if((it + 1) == container.end()){
            return true;
        }
        if(*it > *(it + 1)){
            return false;
        }
    }
    return true;
}
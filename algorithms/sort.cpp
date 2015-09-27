#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

vector<string> string_split(const string &src, const string &separator = string(), int maxsplit = -1)
{
    vector<string> res;

    if (src.empty())
        return res;

    if (maxsplit == 0)
        return vector<string>{ src };

    const char blanks[] = { '\x20', '\n', '\r', '\t', '\f' };
    auto is_blank = [&blanks](const char &c) {
        for (const char &ch : blanks)
            if (c == ch)
                return true;
        return false;
    };

    size_t start, stop;
    for (start = stop = 0; stop < src.size(); ) {
        if (separator.empty()) {
            if (is_blank(src[stop])) {
                if (stop - start > 0) {
                    res.push_back(string(src.c_str() + start, stop - start));
                    start = stop;
                }
                stop++;
                start++;
            } else {
                stop++;
                if (stop == src.size()) {
                    res.push_back(string(src.c_str() + start, stop - start));
                    start = stop;
                }
            }
        } else {
            string::size_type pos = src.find(separator, stop);
            if (pos != string::npos) {
                if (pos - start > 0) {
                    res.push_back(string(src.c_str() + start, pos - start));
                }
                stop = (pos + separator.size());
                start = stop;
            } else {
                res.push_back(string(src.c_str() + stop));
                break;
            }
        }
    }

    return res;
}

void bubble_sort(vector<int> &arr, bool ascending = true, bool stable = true)
{
    if (arr.empty())
        return;

    auto compare = [ascending](int a, int b) {
        if (a > b && ascending)
            return true;
        return false;
    };

    for (size_t i = arr.size() - 1; i > 0; i--) {
        for (size_t j = 0; j < i; j++) {
            if (compare(arr[j], arr[j + 1])) {
                arr[j] ^= arr[j + 1];
                arr[j + 1] ^= arr[j];
                arr[j] ^= arr[j + 1];
            }
        }
    }
}

void insertion_sort(vector<int> &arr, bool ascending = true)
{
    vector<int> res;

    for (size_t i = 0; i < arr.size(); i++) {
        if (res.empty()) {
            res.push_back(arr[i]);
            continue;
        }

        for (vector<int>::iterator iter = res.begin(); iter != res.end(); iter++) {
            if (iter - res.begin() == static_cast<int>(res.size() - 1) &&
                arr[i] >= *iter) {
                res.push_back(arr[i]);
                break;
            }

            if (arr[i] < *iter) {
                res.insert(iter, arr[i]);
                break;
            }

            if (arr[i] >= *iter && arr[i] < *(iter + 1)) {
                res.insert(iter + 1, arr[i]);
                break;
            }
        }
    }

    arr = res;
}

void quick_sort(vector<int> &arr, bool ascending = true)
{
    if (arr.empty())
        return;

    int key = arr[0];
    vector<int> left, right;
    for (int i : arr) {
        if (i <= key)
            left.push_back(i);
        if (i > key)
            right.push_back(i);
    }
}

void get_arr(const string &filename, vector<int> &arr)
{
    FILE *fp = fopen(filename.c_str(), "rb");

    char buf[20] = { 0 };
    string line;
    size_t bytes = 0;
    while ((bytes = fread(buf, 1, sizeof(buf), fp)) > 0) {
        char *needle = strstr(buf, "\n");
        if (needle) {
            line.append(buf, needle - buf);
            break;
        } else {
            line.append(buf, sizeof(buf));
        }

        memset(buf, 0, sizeof(buf));
    }

    fclose(fp);

    cout << "before sort: " << endl;
    cout << line << endl;

    vector<string> str_vec = string_split(line);

    for (string &s : str_vec) {
        arr.push_back(stoi(s));
    }
}

int main(int argc, char **argv)
{
    string filename("exp.data");
    if (argv[1])
        filename = argv[1];

    vector<int> arr;

    get_arr(filename, arr);

//    bubble_sort(arr);
//    insertion_sort(arr);
    quick_sort(arr);

    cout << "after sort: " << endl;
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

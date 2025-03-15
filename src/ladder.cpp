#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    
    if (abs(len1 - len2) > d) return false;

    int count = 0, i = 0, j = 0;

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            count++;
            if (count > d) return false;

            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    
    count += (len1 - i) + (len2 - j);
    
    return count == d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end()) return {};
    
    queue<vector<string>> ladders;
    ladders.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladders.empty()) {
        int level_size = ladders.size();
        set<string> level_visited;

        for (int i = 0; i < level_size; i++) {
            vector<string> current_ladder = ladders.front();
            ladders.pop();
            string last_word = current_ladder.back();

            if (last_word == end_word) return current_ladder;

            for (const string& word : word_list) {
                if (!visited.count(word) && is_adjacent(last_word, word)) {
                    vector<string> new_ladder = current_ladder;
                    new_ladder.push_back(word);
                    ladders.push(new_ladder);
                    level_visited.insert(word);
                }
            }
        }
        for (const string& w : level_visited) {
            visited.insert(w);
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Cannot open file " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No ladder found." << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        if (i > 0) cout << " -> ";
        cout << ladder[i];
    }
    cout << endl;
}

void verify_word_ladder(const vector<string>& ladder, const set<string>& word_list) {
    if (ladder.empty()) {
        cout << "Invalid ladder: Ladder is empty." << endl;
        return;
    }
    for (size_t i = 1; i < ladder.size(); i++) {
        if (!is_adjacent(ladder[i - 1], ladder[i])) {
            error(ladder[i - 1], ladder[i], "Words are not adjacent");
            return;
        }
        if (word_list.find(ladder[i]) == word_list.end()) {
            error(ladder[i - 1], ladder[i], "Word not in dictionary");
            return;
        }
    }
    cout << "Valid ladder!" << endl;
}
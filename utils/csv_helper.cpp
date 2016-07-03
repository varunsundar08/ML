/*
 * This files defines the functions in csv_helper.hpp
 */

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "./csv_helper.hpp"

using namespace std;

/*
 * Returns the size of the file
 */
size_t get_file_size(const string file_name) {
    FILE *fp = NULL;
    fp = fopen(file_name.c_str(), "r");
    assert(fp != NULL && "Can't open csv");
    fseek(fp, 0, SEEK_END);
    size_t file_size = ftell(fp);
    fclose(fp);
    return file_size;
} 

/*
 * Return all the lines in the file.
 */
vector<string> get_lines(const string file_name) {
    /* Open file */
    FILE *fp = NULL;
    fp = fopen(file_name.c_str(), "r");
    assert(fp != NULL && "Can't open csv");
    size_t file_size = get_file_size(file_name); 

    /* Buffer to hold file contents */
    char *file_contents = NULL;
    file_contents = (char *)malloc(file_size + 1);
    assert(file_contents != NULL && "Cannot malloc memory");
    file_contents[file_size] = '\0';

    int num_read = fread(file_contents, 1, file_size, fp);
    assert(num_read == file_size && "File not read properly");

    vector<string> ret_val;
    /* Get lines */;
    char *token = strtok(file_contents, "\n");
    while(token != NULL) {
        ret_val.push_back(string(token));
        token = strtok(NULL, "\n");
    }

    free(file_contents);
    fclose(fp);

    return ret_val;
}

/*
 * Processes each line and gets all the tokens
 */
vector<vector<string> > get_tokens(const vector<string> lines) {
    vector<vector<string> > tokens;
    for(unsigned int line_iter = 0; line_iter < lines.size(); line_iter++) {
        vector<string> tokens_in_line;
        string line = lines[line_iter];
        
        /* Get a mutable line */
        char *mutable_line = NULL;
        mutable_line = (char *)malloc(line.length() + 1);
        for(unsigned int char_iter = 0; char_iter < line.length(); char_iter++) {
            mutable_line[char_iter] = line[char_iter];
        }
        mutable_line[line.length()] = '\0';

        /* Get tokens */
        char *token = strtok(mutable_line, ","); // Support only ',' for now
        while(token != NULL) {
            tokens_in_line.push_back(string(token));
            token = strtok(NULL, ","); // Support only ',' for now
        }
        tokens.push_back(tokens_in_line);

        free(mutable_line);
    }
    return tokens;
}

/*
 * Given a file; returns vector<vector<float> > 
 */
vector<vector<float> > get_tokens_as_float(const string file_name) {
    vector<string> lines = get_lines(file_name);
    vector<vector<string> > tokens = get_tokens(lines);
    vector<vector<float> > tok_as_float;

    for(unsigned int token_i = 0; token_i < tokens.size(); token_i++) {
        vector<float> ip;
        for(unsigned int token_j = 0; token_j < tokens[token_i].size(); token_j++) {
            double value = atof(tokens[token_i][token_j].c_str());
            ip.push_back((float)value);
        }
        tok_as_float.push_back(ip);
    }
    return tok_as_float;
}


/*
 * csv file -> vector<vector<float> >;
 * supports only ',' as a delimiter;
 * This is a wrapper function that just called get_tokens_as_float 
 */
vector<vector<float> > csv_vec_vec_float(const string file_name) {
    return get_tokens_as_float(file_name);
}
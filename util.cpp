#include "util.hpp"
using namespace std;
using namespace std::filesystem;

namespace util {
    string readFile(string fname) {
        // https://stackoverflow.com/a/2602258/14639101
        std::ifstream t(fname);
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }
 
    vector<string> split(string splitting, char delimiter) { // https://stackoverflow.com/a/10058725

        stringstream tosplit(splitting);
        string segment;
        vector<string> seglist;

        while(getline(tosplit, segment, delimiter)) {
            //cout << segment << endl;
            seglist.push_back(segment);
        }

        return seglist;
    }

    string join(vector<string> v, string delimiter) { // https://stackoverflow.com/a/20986194
        stringstream ss;
        const int v_size = v.size();
        for(size_t i = 0; i < v_size; ++i)
        {
            if(i != 0)
                ss << delimiter;
            ss << v[i];
        }
        string s = ss.str();

        return s;
    }

    vector<string> wrap(vector<string> towrap) {
        vector<string> wrappedv = {};

        for (string const& arg : towrap) {
            string wrapped = "\"" + arg + "\"";
            wrappedv.push_back(wrapped);
        }

        return wrappedv;
    }

    vector<string> getFiles(string dir) {
        vector<string> files = {};

        for(auto const& dir_entry: recursive_directory_iterator{dir}) {
            files.push_back(dir_entry.path());
        }

        return files;
    }

    vector<string> filterFiles(vector<string> files, vector<string> exts) {
        vector<string> ffiles = {};

        for (string const& file : files) {
            string sfile = split(file, '/').back();
            if (sfile.find(".") == string::npos) {
                continue;
            }

            string fext = split(sfile, '.').back();
            bool inexts = false;
            for (string const& ext : exts) {
                if ((fext == ext)) {
                    inexts = true;
                    break;
                }
            } 

            if (inexts) {
                ffiles.push_back(file);
            }

        } // I am disgusted by whatever this is that I have just made, but it works.

        return ffiles;
    }

    string replaceExt(string filename, string newext) {
        vector<string> splt = split(filename, '.');
        splt[splt.size() - 1] = newext;
        return join(splt, ".");
    }

    vector<string> replaceExts(vector<string> files, string newext) {
        vector<string> newfiles = {};
        for (string const& file : files) {
            newfiles.push_back(replaceExt(file, newext));
        }
        return newfiles;
    }

    bool startsWith(string str, string strwth) {
        return str.rfind(strwth, 0) == 0;
    }

    std::vector< std::vector<string> > splitvs(std::vector<string> vec, int n) {
        std::vector< std::vector<string> > vec_of_vecs(n); // https://stackoverflow.com/a/48739993

        int quotient = vec.size() / n;
        int remainder = vec.size() % n;
        int first = 0;
        int last;
        for (int i = 0; i < n; ++i) {
            if (i < remainder) {
                last = first + quotient + 1;
                vec_of_vecs[i] = std::vector<string>(vec.begin() + first, vec.begin() + last);
                first = last;
            } else if (i != n - 1) {
                last = first +  quotient;
                vec_of_vecs[i] = std::vector<string>(vec.begin() + first, vec.begin() + last);
                first = last;
            } else {
                vec_of_vecs[i] = std::vector<string>(vec.begin() + first, vec.end());
            }
        }

        return vec_of_vecs;
    }

}
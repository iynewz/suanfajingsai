#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "grade.h"
#include "Student_info.h"

using std::cout;
using std::domain_error;
using std::istream;
using std::sort;
using std::vector;

// code is taken from §4.1.1/53
// compute the median of a vector<double>
// note that calling this function copies the entire argument vector
double median(vector<double> vec)
{
    typedef vector<double>::size_type vec_sz;

    vec_sz size = vec.size();
    if (size == 0)
        throw domain_error("median of an empty vector");

    sort(vec.begin(), vec.end());

    vec_sz mid = size / 2;

    return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

// code taken from §4.1/52
// compute a student's overall grade from midterm and final exam grades and homework grade
double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

// code taken from §4.1.2/54
// compute a student's overall grade from midterm and final exam grades
// and vector of homework grades.
// this function does not copy its argument, because median does so for us.
double grade(double midterm, double final, const vector<double> &hw)
{
    if (hw.size() == 0)
        throw domain_error("student has done no homework");
    return grade(midterm, final, median(hw));
}

// code is taken from §4.4/69
bool compare(const Student_info &x, const Student_info &y)
{
    return x.name < y.name;
}

istream &read(istream &is, Student_info &s)
{
    double midterm, final;
    vector<double> homework;
    // read and store the student's name and final grade
    is >> s.name >> midterm >> final;

    // handle end-of-file
    if (is)
    {
        read_hw(is, homework);
        // save only the final grade
        s.final_grade = grade(midterm, final, homework);
    }

    return is;
}

// code is taken from §4.1.3/57
istream &read_hw(istream &in, vector<double> &hw)
{
    if (in)
    {
        // get rid of previous contetns
        hw.clear();

        // read homework grades
        double x;
        while (in >> x)
            hw.push_back(x);

        // clear the stream so that input will work for the next student
        in.clear();
    }
    return in;
}

int main()
{
    return 0;
}
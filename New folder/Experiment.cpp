#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// Base class Land
class Land
{
protected:
    int land_area = 0;

public:
    Land(int x) : land_area(x) {}

    int get_land() const
    {
        return land_area;
    }
};

// Derived class Division
class Division : public Land
{
protected:
    string div_name;

public:
    Division(string s, int x) : Land(x), div_name(s) {}

    string get_division() const
    {
        return div_name;
    }

    // Overloading the << operator to display Division information
    friend ostream& operator<<(ostream& os, const Division& division)
    {
        os << division.get_division() << " (Land Area: " << division.get_land() << ")";
        return os;
    }
};

// Derived class District
class District : public Division
{
protected:
    string dis_name;

public:
    District(string s, string s1, int x) : Division(s1, x), dis_name(s) {}

    string get_district() const
    {
        return dis_name;
    }

    // Overloading the << operator to display District information
    friend ostream& operator<<(ostream& os, const District& district)
    {
        os << district.get_district() << " (Area: " << district.get_land() << ") - Division: " << district.get_division();
        return os;
    }
};

// Function to add a District to a Division and save it in a file
void addDistrictToDivision(string divisionName, District district)
{
    ofstream f_dv;
    f_dv.open(divisionName + ".txt", ios::app);
    f_dv << district.get_district() << " " << district.get_land() << endl;
    f_dv.close();
}

// Function to calculate the total land area of a Division or Bangladesh
int totalLandArea(string A)
{
    ifstream f1(A + ".txt");
    int total = 0, landArea;
    string S, DistrictNaam;
    while (getline(f1, S))
    {
        istringstream iss(S);
        iss >> DistrictNaam >> landArea;
        total += landArea;
    }
    f1.close();
    return total;
}

// Function to update the land area of a Division
void updateDivisionLand(string S, string S1, int total)
{
    fstream file(S + ".txt", ios::in);
    string line;
    int total_line = 0, desired_line = 0;
    vector<string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
        total_line++;
        string divisionName;
        int landArea;
        istringstream iss(line);
        iss >> divisionName >> landArea;
        if (divisionName == S1)
            desired_line = total_line;
    }
    file.close();
    ofstream file1;
    file1.open(S + ".txt", ios::out);
    if (file1.fail())
    {
        cout << "Error opening file.\n" << endl;
        return;
    }
    desired_line--;
    for (int i = 0; i < lines.size(); i++)
    {
        if (i != desired_line)
            file1 << lines[i] << endl;
        else
            file1 << S1 << " " << total << endl;
    }
    file1.close();
}

int main()
{
    string S = "Bangladesh";
    int a, choice;

    // Program header
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
    cout << "> > > > > > > > > > > > >\t\t\tB  A  N  G  L  A  D  E  S  H\t\t\t< < < < < < < < < < < <  \n";
    cout << "> > > > > > > > > > > > >\t\t\t      D E C E M B E R      \t\t\t< < < < < < < < < < < <  \n";
    cout << "> > > > > > > > > > > > >\t\t\t\t  1 9 7 1                \t\t< < < < < < < < < < < <  \n";
    cout << "General Muhammad Ataul Ghani Osmani maintained a private note containing the names of districts he had successfully made independent, along with their respective land areas. This information was organized within a page titled \"Division\". Furthermore, the division names were recorded in a separate note titled \"Bangladesh\".\n"
         << endl;

    do {
        // Menu options
        cout << "1. Add a Division\n";
        cout << "2. Add a District\n";
        cout << "3. Modify a District\n";
        cout << "4. Total land area of Bangladesh\n";
        cout << "5. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Add a Division
            cout << "Enter Division Name: ";
            string name;
            int area;
            cin >> name >> area;

            Division d1(name, area);

            ofstream f;
            f.open(S + ".txt", ios::app);
            f << d1.get_division() << " " << d1.get_land() << endl;
            cout << endl << "Added Division: " << d1 << endl << endl;
            f.close();

            break;
        }

        case 2:
        {
            // Add a District
            cout << "Enter District Name & Area: ";
            string ds_name;
            int disArea;
            cin >> ds_name >> disArea;

            cout << "Enter Division Name (it belongs to): ";
            string dv_name, X;
            cin >> dv_name;

            District d2(ds_name, dv_name, disArea);
            int flag = 1;

            ifstream f(S + ".txt");
            while (getline(f, X))
            {
                string divisionName;
                int landArea;

                istringstream iss(X);
                iss >> divisionName >> landArea;
                if (divisionName == dv_name)
                {
                    flag = 0;
                    addDistrictToDivision(dv_name, d2);
                    cout << endl << "Added District: " << d2 << endl << endl;
                    a = totalLandArea(dv_name);
                }
            }
            if (flag)
            {
                ofstream f_dv;
                f_dv.open(S + ".txt", ios::app);
                f_dv << d2.get_division() << " " << d2.get_land() << endl;
                f_dv.close();

                addDistrictToDivision(dv_name, d2);
                cout << endl << "Added District: " << d2 << endl << endl;
                a = totalLandArea(dv_name);
            }
            updateDivisionLand(S, dv_name, a);
            break;
        }
        case 3:
        {
            // Modify a District
            cout << "Enter the District Name with Division Name: ";
            string dis_name, div_name;
            cin >> dis_name >> div_name;
            cout << "Enter New Area Acquired: ";
            int land, land1;
            int total_line = 0, desired_line = 0;
            cin >> land;
            fstream file2(div_name + ".txt", ios::in);
            string line, district_name;
            vector<string> lines;
            while (getline(file2, line))
            {
                lines.push_back(line);
                total_line++;
                istringstream iss(line);
                iss >> district_name >> land1;
                if (dis_name == district_name)
                {
                    land += land1;
                    desired_line = total_line;
                }
            }
            file2.close();
            ofstream file3;
            file3.open(div_name + ".txt", ios::out);
            if (file3.fail())
            {
                cout << "Error opening file.\n" << endl;
                return 1;
            }
            desired_line--;
            for (int i = 0; i < lines.size(); i++)
            {
                if (i != desired_line)
                    file3 << lines[i] << endl;
                else
                    file3 << dis_name << " " << land << endl;
            }
            file3.close();
            a = totalLandArea(div_name);
            updateDivisionLand(S, div_name, a);
            cout << endl << "New Area of " << dis_name << " is: " << land << endl << endl;
            break;
        }
        case 4:
        {
            // Total land area of Bangladesh
            cout << endl << "Now Total Land Area of Bangladesh: " << totalLandArea(S) << endl << endl;
            break;
        }
        }
    } while (choice != 5);
    return 0;
}

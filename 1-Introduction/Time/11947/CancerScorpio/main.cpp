#include <iostream>
#include <string>
#include <map>

using namespace std;

static const map<int, string> zodiacSigns{
    {1, "capricorn"},
    {21, "aquarius"},
    {51, "pisces"},
    {80, "aries"},
    {111, "taurus"},
    {142, "gemini"},
    {173, "cancer"},
    {204, "leo"},
    {234, "virgo"},
    {267, "libra"},
    {297, "scorpio"},
    {327, "sagittarius"},
    {357, "capricorn"}};

static const map<int, int> monthDays{
    {1, 0},
    {2, 31},
    {3, 59},
    {4, 90},
    {5, 120},
    {6, 151},
    {7, 181},
    {8, 212},
    {9, 243},
    {10, 273},
    {11, 304},
    {12, 334}};

bool isLeapYear(int year)
{
  return !(year % 4) && ((year % 100) || !(year % 400));
}

int getNofYearDay(int day, int month, int year)
{
  bool leap = isLeapYear(year);
  int yearDay = 1;

  map<int, int>::const_iterator monthIter = monthDays.find(month);

  if (monthIter != monthDays.end())
  {
    yearDay = monthIter->second + day;

    yearDay += ((yearDay > 59) && leap) ? 1 : 0;
  }

  return yearDay;
}

string getYearDayAsString(int yearDay, int year)
{
  int day = 0;
  int month = 0;

  for (map<int, int>::const_reverse_iterator it = monthDays.rbegin();
       it != monthDays.rend(); ++it)
  {
    if (yearDay > it->second)
    {
      month = it->first;
      day = yearDay - it->second;
      break;
    }
  }

  if (isLeapYear(year) && yearDay > 59)
  {
    day--;
    if (yearDay == 60)
    {
      day = 29;
      month--;
    }
    else if (day == 0)
    {
      day = monthDays.at(month--) - monthDays.at(month);
    }
  }

  string monthStr = to_string(month);
  string dayStr = to_string(day);

  monthStr = (month < 10) ? "0" + monthStr : monthStr;
  dayStr = (day < 10) ? "0" + dayStr : dayStr;

  return monthStr + "/" + dayStr + "/" + to_string(year);
}

void checkCancerOrScorpio(string date, int nofExp)
{
  char dayCh[]{
      date[2],
      date[3],
      '\0'};

  char monthCh[]{
      date[0],
      date[1],
      '\0'};

  int day = atoi(dayCh);
  int month = atoi(monthCh);
  int year = stoi(date.substr(4, 7));

  int yearDay = getNofYearDay(day, month, year);
  int yearLimit = isLeapYear(year) ? 366 : 365;

  yearDay += 280;

  if (yearDay > yearLimit)
  {
    yearDay -= yearLimit;
    year++;
  }

  for (map<int, string>::const_reverse_iterator it = zodiacSigns.rbegin();
       it != zodiacSigns.rend(); ++it)
  {
    if (yearDay >= it->first)
    {
      cout << nofExp << " " << getYearDayAsString(yearDay, year) << " "
           << it->second << endl;
      break;
    }
  }
}

void parseinput()
{
  int numOfExperiments = 0, iter = 1;
  string fullDate;

  cin >> numOfExperiments;

  while (numOfExperiments-- > 0)
  {
    cin >> fullDate;
    checkCancerOrScorpio(fullDate, iter++);
  }
}

int main()
{
  parseinput();
  return 0;
}
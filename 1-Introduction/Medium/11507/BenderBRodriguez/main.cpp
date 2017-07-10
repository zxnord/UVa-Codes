#include <array>
#include <iostream>
#include <list>

//-----------------------------------------------------------------------------

bool processGenericValue(int &val, int sum)
{
  val += sum;
  if ((val >= 2) || (val <= -2))
  {
    return true;
  }
  return false;
}

//-----------------------------------------------------------------------------

bool processXValueNode(std::array<int, 3> &exp, bool neg)
{
  if (exp[1] && neg)
  {
    exp[1] *= -1;
    return true;
  }

  return false;
}

//-----------------------------------------------------------------------------

bool processValueNode(std::array<int, 3> &exp, int yOrz, bool neg)
{
  int sum = neg ? -1 : 1;

  if (exp[yOrz])
  {
    if (processGenericValue(exp[yOrz], sum))
    {
      exp[0] = -1;
      exp[1] = 0;
      exp[2] = 0;
    }
    else if (exp[yOrz] == 0)
    {
      exp[0] = 1;
      exp[1] = 0;
      exp[2] = 0;
    }

    return true;
  }
  else if (exp[0])
  {
    exp[yOrz] = sum * exp[0];
    exp[0] = 0;
  }

  return false;
}

//-----------------------------------------------------------------------------

void addNewNode(std::list<std::array<int, 3>> &expList,
                const std::array<int, 3> &node)
{
  for (auto exp = expList.begin(); exp != expList.end(); ++exp)
  {
    bool updateNode = false;

    if (node[0])
    {
      updateNode = processXValueNode(*exp, (node[0] < 0));
    }
    else if (node[1])
    {
      updateNode = processValueNode(*exp, 1, (node[1] < 0));
    }
    else if (node[2])
    {
      updateNode = processValueNode(*exp, 2, (node[2] < 0));
    }
  }

  expList.push_front(node);
}

//-----------------------------------------------------------------------------

void printExpResult(const std::array<int, 3> &exp)
{
  auto printRes = [](int val, unsigned char axis) {
    unsigned char s = (val > 0) ? '+' : '-';

    std::cout << s << axis << std::endl;
  };

  if (exp[0])
  {
    printRes(exp[0], 'x');
  }
  else if (exp[1])
  {
    printRes(exp[1], 'y');
  }
  else if (exp[2])
  {
    printRes(exp[2], 'z');
  }
}

//-----------------------------------------------------------------------------

void parseInput()
{
  int lenght = 0;

  while ((std::cin >> lenght) && (lenght > 0))
  {
    std::string line;
    std::list<std::array<int, 3>> expList;

    std::cin.ignore();
    std::getline(std::cin, line);

    for (int i = 0; i < 3 * (lenght - 1); i += 3)
    {
      int signMultiplier;
      unsigned char sign, axis;
      std::array<int, 3> node{0, 0, 0};

      sign = line[i];
      axis = line[i + 1];

      signMultiplier = (sign == '-') ? -1 : (sign == '+') ? 1 : 0;

      auto assignValue = [&node, &signMultiplier](int i) {
        node[i] = 1 * signMultiplier;
      };

      switch (axis)
      {
      case 'x':
        assignValue(0);
        break;

      case 'y':
        assignValue(1);
        break;

      case 'z':
        assignValue(2);
        break;

      case 'o':
      default:
        node[0] = 1;
        break;
      }

      addNewNode(expList, node);
    }

    printExpResult(expList.back());
  }
}

//-----------------------------------------------------------------------------

int main()
{
  parseInput();
  return 0;
}

//-----------------------------------------------------------------------------

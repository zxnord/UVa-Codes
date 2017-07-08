#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <limits>

//------------------------------------------------------------------------------


struct Proposal
{
  std::string name;
  float price;
  int numOfReqsMet;
};

//------------------------------------------------------------------------------

void processNewExperiment(
  const std::unordered_set<std::string>& reqsSet,
  int numExpProposals,
  int requirements)
{
  static int numberOfExperiments = 1;
  std::string result = "None";
  double bestCompliance = 0.0;
  float bestPrice = std::numeric_limits<float>::max();

  for( int i = 0; i < numExpProposals; ++i )
  {
    struct Proposal newProp;
    int propRequirements;

    std::cin >> newProp.name;
    std::cin >> newProp.price >> propRequirements;

    newProp.numOfReqsMet = 0;

    std::cin.ignore();

    for( int j = 0; j < propRequirements; ++j )
    {
      std::string currentReq;

      std::getline(std::cin, currentReq);

      if( reqsSet.find(currentReq) != reqsSet.end() )
      {
        ++newProp.numOfReqsMet;
      }
    }

    double currentCompliance =
      double( newProp.numOfReqsMet ) / double( requirements );

    if( (currentCompliance > bestCompliance) ||
      ((currentCompliance == bestCompliance) &&
        (newProp.price < bestPrice)) )
    {
      bestCompliance = currentCompliance;
      bestPrice = newProp.price;
      result = newProp.name;
    }
  }

  std::cout << "RFP #" << numberOfExperiments++ << std::endl;
  std::cout << result << std::endl << std::endl;
}

//------------------------------------------------------------------------------

void parseInput()
{
  int requirements, proposals;
  std::unordered_set<std::string> reqsSet;

  std::cin >> requirements >> proposals;
  std::cin.ignore();

  while( (requirements != 0) && (proposals != 0) )
  {
    for( int i = 0; i < requirements; ++i )
    {
      std::string req;
      std::getline(std::cin, req);

      reqsSet.insert(req);
    }

    processNewExperiment(reqsSet, proposals, requirements);

    std::cin >> requirements >> proposals;
    std::cin.ignore();
  }
}

//------------------------------------------------------------------------------

int main()
{
  parseInput();
  return 0;
}

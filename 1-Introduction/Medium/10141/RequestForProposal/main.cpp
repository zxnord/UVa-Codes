#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>

//------------------------------------------------------------------------------


struct Proposal
{
  std::string name;
  float price;
  int numOfReqsMet;
};

//------------------------------------------------------------------------------

void checkResult(
  const std::vector<struct Proposal>& expProposals,
  int numOfRequirements)
{
  static int numberOfExperiments = 1;
  std::string result = "None";
  double bestCompliance = 0.0;
  float bestPrice = std::numeric_limits<float>::max();

  for( const auto& prop : expProposals )
  {
    double currentCompliance =
      double( prop.numOfReqsMet ) / double( numOfRequirements );

    if( (currentCompliance > bestCompliance) ||
      ((currentCompliance == bestCompliance) &&
        (prop.price < bestPrice)) )
    {
      bestCompliance = currentCompliance;
      bestPrice = prop.price;
      result = prop.name;
    }
  }

  std::cout << "RFP #" << numberOfExperiments++ << std::endl;
  std::cout << result << std::endl << std::endl;
}

//------------------------------------------------------------------------------

void processNewExperiment(
  const std::unordered_map<std::string, bool>& reqsMap,
  int numExpProposals,
  int requirements)
{
  std::vector<struct Proposal> expProposals;

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

      if( reqsMap.find(currentReq) != reqsMap.end() )
      {
        ++newProp.numOfReqsMet;
      }

    }

    expProposals.push_back(newProp);
  }

  checkResult(expProposals, requirements);
}

//------------------------------------------------------------------------------

void parseInput()
{
  int requirements, proposals;
  std::unordered_map<std::string, bool> reqsMap;

  std::cin >> requirements >> proposals;
  std::cin.ignore();

  while( (requirements != 0) && (proposals != 0) )
  {
    for( int i = 0; i < requirements; ++i )
    {
      std::string req;
      std::getline(std::cin, req);

      if( reqsMap.find(req) == reqsMap.end() )
      {
        reqsMap[req] = true;
      }
    }

    processNewExperiment(reqsMap, proposals, requirements);

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

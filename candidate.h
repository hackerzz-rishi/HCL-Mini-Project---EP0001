#ifndef CANDIDATE 
#define CANDIDATE

#include <string>

class Candidate {
public:
    // Constructor for a candidate.
    //
    // Args:
    //   id: The candidate's unique ID.
    //   name: The candidate's name.
    //   symbol: The candidate's party symbol.
    //   reg: The candidate's region ID.
    //   votes: The initial number of votes (default: 0).
    Candidate(const std::string& id, const std::string& name, const std::string& symbol,
              const std::string& regionCode, int votes = 0);

    // Getters and setters for candidate properties.
    std::string GetCandidateID() const;
    std::string GetCandidateName() const;
    std::string GetPartySymbol() const;
    std::string GetRegion() const;
    int GetNumOfVotes() const;

    void SetCandidateID(const std::string& id);
    void SetCandidateName(const std::string& name);
    void SetPartySymbol(const std::string& symbol);
    void SetRegion(const std::string& regionCode);
    void SetVotes(int votes);

private:
    // Candidate attributes.
    std::string candidateID;
    std::string candidateName;
    std::string partySymbol;
    std::string regionID;
    int numOfVotes;
};

#endif

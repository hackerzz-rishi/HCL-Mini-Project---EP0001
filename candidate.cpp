#include "candidate.h"

// Constructor for a candidate.
//
// Args:
//   id: The candidate's unique ID.
//   name: The candidate's name.
//   symbol: The candidate's party symbol.
//   reg: The candidate's region ID.
//   votes: The initial number of votes (default: 0).
Candidate::Candidate(const std::string& id, const std::string& name, const std::string& symbol,
                     const std::string& regionCode, int votes)
    : candidateID(id), candidateName(name), partySymbol(symbol), regionID(regionCode), numOfVotes(votes) {
}

// Getters and setters for candidate properties.
std::string Candidate::GetCandidateID() const { return candidateID; }
std::string Candidate::GetCandidateName() const { return candidateName; }
std::string Candidate::GetPartySymbol() const { return partySymbol; }
std::string Candidate::GetRegion() const { return regionID; }
int Candidate::GetNumOfVotes() const { return numOfVotes; }

void Candidate::SetCandidateID(const std::string& id) { candidateID = id; }
void Candidate::SetCandidateName(const std::string& name) { candidateName= name; }
void Candidate::SetPartySymbol(const std::string& symbol) { partySymbol= symbol; }
void Candidate::SetRegion(const std::string& regionCode) { regionID= regionCode; }
void Candidate::SetVotes(int votes) { numOfVotes = votes; }

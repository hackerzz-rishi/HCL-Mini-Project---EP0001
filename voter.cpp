#include "voter.h"

// Class representing a voter in an election.

// Constructor for a voter.
//
// Args:
//   aadhar: The voter's Aadhaar ID.
//   status: The voter's initial voting status (default: false, indicating
//           they haven't voted yet).
Voter::Voter(const std::string& aadhar, bool status)
    : aadhaarID(aadhar), votingStatus(status) {}

// Getters and setters for voter properties.
std::string Voter::GetAadharID() const { return aadhaarID; }
void Voter::SetAadharID(const std::string& aadhar) { aadhaarID = aadhar; }
bool Voter::GetVotingStatus() const { return votingStatus; }
void Voter::SetVotingStatus(bool currentStatus) { votingStatus = currentStatus; }

#ifndef VOTER
#define VOTER

#include <string>

// Class representing a voter in an election.
class Voter {
public:
    // Constructor for a voter.
    //
    // Args:
    //   aadhar: The voter's Aadhaar ID.
    //   status: The voter's initial voting status (default: false, indicating
    //           they haven't voted yet).
    Voter(const std::string& aadhar, bool status = false);

    // Getters and setters for voter properties.
    std::string GetAadharID() const;
    void SetAadharID(const std::string& aadhar);
    bool GetVotingStatus() const;
    void SetVotingStatus(bool currentStatus);

private:
    // Voter attributes.
    std::string aadhaarID;  // The voter's unique Aadhaar ID.
    bool votingStatus;      // Indicates whether the voter has already voted.
};

#endif

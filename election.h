#ifndef ElECTION 
#define ElECTION

#include "candidate.h"
#include "voter.h"

#include <iostream>  // C++ standard library header
#include <cctype>    // C++ standard library header
#include <algorithm> // C++ standard library header
#include <limits>    // C++ standard library header
#include <string>    // C++ standard library header
#include <map>       // C++ standard library header
#include <set>       // C++ standard library header
#include <vector>    // C++ standard library header
#include <unordered_map>  // C++ standard library header
#include <fstream>   // C++ standard library header
#include <sstream>   // C++ standard library header

// Class representing the core functionality of the election management system.
class ElectionSystem {
 private:
  // Stores valid admin credentials read from the CSV file.
  std::unordered_map<std::string, std::string> adminValidate;

  // Containers for valid and invalid candidate and voter data.
  std::vector<Candidate> invalidCandidateList;
  std::vector<Candidate> validCandidateList;
  std::vector<Voter> validVoterList;
  std::vector<std::pair<std::string, std::string>> invalidVoterList;


  // Sets for ensuring uniqueness of candidate IDs ,party symbols , aadhar IDs.
  std::set<std::string> idSet;
  std::set<std::string> symbolSet;
  std::set<std::string> checkAadhar;

  // Stores the current vote count for each candidate.
  std::map<std::string, int64_t> votesSet;

  // Stores any error messages for reporting to the user.
  std::string errorMessage;

  public:
  
  // Reads admin credentials from a CSV file, validates them, and stores valid pairs.
  //
  // Returns:
  //   true if at least one valid admin is found, false otherwise.
  bool AdminCsvCheck();

  
  // Calculates a simple checksum by shifting each character in the message by a fixed value.
  //
  // Args:
  //   message: The string for which to calculate the checksum.
  //
  // Returns:
  //   The calculated checksum as a string.
  std::string CalculateCheckSum(const std::string& message);

  
  // Validates a candidate ID based on uniqueness, format, and character composition.
  //
  // Args:
  //   id: The candidate ID to validate.
  //
  // Returns:
  //   true if the ID is valid, false otherwise.
  bool ValidateCandidateID(const std::string& id);


  // Validates a candidate name based on length and character composition.
  //
  // Args:
  //   name: The candidate name to validate.
  //
  // Returns:
  //   true if the name is valid, false otherwise.
  bool ValidateCandidateName(const std::string& name);


  // Validates a party symbol based on uniqueness, length, and character composition.
  //
  // Args:
  //   symbol: The party symbol to validate.
  //
  // Returns:
  //   true if the symbol is valid, false otherwise.
  bool ValidatePartySymbol(const std::string& symbol);


  // Validates a region code based on its format and character composition.
  //
  // Args:
  //   code: The region code to validate.
  //
  // Returns:
  //   true if the code is valid, false otherwise.
  bool ValidateRegionCode(const std::string& code);


  // Determines whether a given string represents a valid non-negative integer.
  //
  // Args:
  //   str: The string to validate.
  //
  // Returns:
  //   true if the string is a valid non-negative integer, false otherwise.
  bool IsValidNumber(const std::string& str);


  // Converts a string to a non-negative integer, returning 0 on failure.
  //
  // Args:
  //   str: The string to convert.
  //
  // Returns:
  //   The converted non-negative integer value, or 0 if conversion fails.
  int Convert2Int(const std::string& str);


  // Validates candidate information from a CSV file and processes valid candidates.
  //
  // Returns:
  //   true if at least one valid candidate was found, false otherwise.
  bool CandidateCsvCheck();


  // Validates voter information from a CSV file and processes valid voters.
  //
  // Returns:
  //   true if at least one valid voter was found, false otherwise.
  bool VoterCsvCheck() ;
  
  bool IsValidAadhar(const std::string& aadhar);

  bool IsValidStatus(const std::string& status) ;
  
  // Repeatedly prompts the user to enter a valid integer choice.
  //
  // Returns:
  //   The valid integer entered by the user.
  int GetChoice();
  

  
  // Repeatedly prompts the user to enter a valid string for a given field.
  //
  // Args:
  //   fieldName: The name of the field to prompt for.
  //
  // Returns:
  //   The valid string entered by the user.
  std::string GetValidString(const std::string& fieldName);


  // Repeatedly prompts the user to enter a valid character for a given field.
  //
  // Args:
  //   fieldName: The name of the field to prompt for.
  //
  // Returns:
  //   The valid character entered by the user.
  char GetValidChar(const std::string& fieldName);


  // Repeatedly prompts the user for admin credentials until successful or cancelled.
  //
  // Returns:
  //   true if authentication is successful, false if the user cancels.
  bool GetAdminAuthenicate() ;


  // Gathers valid candidate information from the user and adds it to the valid_candidate_list_.
  //
  // Returns:
  //   true if a candidate was successfully added, false if the user cancelled.
  bool AddCandidate();
  

  // Identifies and guides the user to fill missing or invalid information in invalid_candidate_list_.
  //
  // Returns:
  //   true if candidates were successfully updated, false if the user cancelled.
  bool FillMissingCandidateInfo();


  // Removes a candidate from the valid_candidate_list_ based on their ID.
  //
  // Returns:
  //   true if a candidate was successfully removed, false if the user cancelled.
  bool RemoveCandidate() ;


  // Modifies a candidate's information in the valid_candidate_list_.
  //
  // Returns:
  //   true if a candidate was successfully modified, false if the user cancelled.
  bool ModifyCandidate();
  
  
  // Adds a new voter to the valid_voter_listt_ container.
  //
  // Returns:
  //   true if a voter was successfully added, false if the user cancelled.
  bool AddVoter();


  // Modifies the information of an existing voter in the valid_voter_listt_.
  //
  // Returns:
  //   true if a voter was successfully modified, false if the user cancelled.  
  bool ModifyVoter();


  // Removes a voter from the valid_voter_listt_ and check_aadhar_ containers.
  //
  // Returns:
  //   true if a voter was successfully removed, false if the user cancelled.
  bool RemoveVoter();

  // Casts a vote for the specified candidate and updates the voter's status.
  //
  // Returns:
  //   true if a vote was successfully cast, false if the user cancelled or an error occurred
  bool CastVote();

  // Displays the vote count for a specific candidate.
  //
  // Returns:
  //   true if the result was displayed successfully, false if the user cancelled or an error occurred.
  bool IndividualResult();

  // Displays the overall election results in descending order of vote count.
  //
  // Returns:
  //   true if the results were displayed successfully
  bool ShowResult();

  
  // Attempts to fill missing or correct invalid voter information.
  //
  // Returns:
  //   true if the information was updated successfully, false if the user cancelled or an error occurred. 
  bool FillMissingVoterInfo();


  // Writes the valid voter data to a CSV file
  void WriteVoterDataToCSV() ;


   // Writes the valid candidate data to a CSV file
  void WriteCandidateDataToCSV() ;


  void WriteResultDataToCSV();
   
  // Destructor for the ElectionSystem class.
  // Writes election results, voter data, and candidate data to CSV files.
  ~ElectionSystem();
 
  // Checks if there are enough valid voters and candidates to conduct an election.
  //
  // Returns:
  //   true if there's at least one valid voter and one valid candidate, false otherwise.
  bool checkCast();

  // Checks if there are  candidates to show result.
  //
  // Returns:
  //   true if there's at least one valid candidate, false otherwise.
  bool checkCandidate();

};


#endif
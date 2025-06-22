
  #include "election.h"


  // Class representing the core functionality of the election management system.

  // Reads admin credentials from a CSV file, validates them, and stores valid pairs.
  //
  // Returns:
  //   true if at least one valid admin is found, false otherwise.

  bool ElectionSystem::AdminCsvCheck() 
  {
    // Open the CSV file containing admin credentials.
    std::ifstream adminInputFile("Admin.csv"); 

    // Check if the file was opened successfully.
    if (!adminInputFile.is_open()) 
    {
      std::cerr << "Error opening the Admin file.\n";
      return false;
    }

    // Process each line in the CSV file.
    std::string line;
    while (std::getline(adminInputFile, line)) 
    {
      std::istringstream ss(line);
      std::string username, password, hash;

      // Extract username, password, and hash from the line.
      if (std::getline(ss, username, ',') &&
          std::getline(ss, password, ',') &&
          std::getline(ss, hash, ',')) 
       {
        // Validate the credentials by checking the checksum.
        if (CalculateCheckSum(username + password) == hash)
        {
          // Store the valid username-password pair.
          adminValidate[username] = password;
        }
        else
        {
          std::cerr << "checksum does not match\n";
        }
      } 
      else
      {
        std::cerr << "Invalid Format Skipping line " << line << '\n';
      }
    }

    // Close the CSV file.
    adminInputFile.close();

    // Return true if at least one valid admin was found.
    return adminValidate.size() >= 1;
  }

  // Calculates a simple checksum by shifting each character in the message by a fixed value.
  //
  // Args:
  //   message: The string for which to calculate the checksum.
  //
  // Returns:
  //   The calculated checksum as a string.
  std::string ElectionSystem::CalculateCheckSum(const std::string& message) 
{
   std::string hash = "";
   int shift = 5;

   for (unsigned char ch : message)
   {
     hash += static_cast<char>(ch + shift);
   }

   return hash;
}

  
  // Validates a candidate ID based on uniqueness, format, and character composition.
  //
  // Args:
  //   id: The candidate ID to validate.
  //
  // Returns:
  //   true if the ID is valid, false otherwise.
bool ElectionSystem::ValidateCandidateID(const std::string& id)
{
    if (idSet.find(id) != idSet.end())
    {
        errorMessage = "Candidate ID already exists. Please enter a different ID.";
        return false;
    }

    if (id.length() < 3 || id.length() > 5 ||
        !std::any_of(id.begin(), id.end(), ::isdigit) ||
        !std::any_of(id.begin(), id.end(), ::isalpha))
    {
        errorMessage = "Invalid Candidate ID format.";
        return false;
    }

    if (std::none_of(id.begin(), id.end(), ::isdigit) ||
        std::none_of(id.begin(), id.end(), ::isalpha))
    {
        errorMessage = "Candidate ID should contain at least one alpha and one numeric character.";
        return false;
    }

    errorMessage = "";
    return true;
}

  // Validates a candidate name based on length and character composition.
  //
  // Args:
  //   name: The candidate name to validate.
  //
  // Returns:
  //   true if the name is valid, false otherwise.
  bool ElectionSystem::ValidateCandidateName(const std::string& name)
  {
    // Validate the length of the name:
    // - Must be between 2 and 20 characters.
    if (name.length() < 2 || name.length() > 20)
    {
      // error message about Length.
      errorMessage =  "Invalid Candidate Name length.";
      return false;
    }

    // Validate the format of the name:
    // - Must consist only of alphabetic characters (A-Z, a-z).
    if (!std::all_of(name.begin(), name.end(), ::isalpha)) 
    {
      // error message about non-alphabetic characters.
      errorMessage = "Invalid characters in Candidate Name. Only alphabets are allowed.";
      return false;
    }

    // If all validations pass, the name is considered valid.
    errorMessage = "";
    return true;
  }


  // Validates a party symbol based on uniqueness, length, and character composition.
  //
  // Args:
  //   symbol: The party symbol to validate.
  //
  // Returns:
  //   true if the symbol is valid, false otherwise.
  bool ElectionSystem:: ValidatePartySymbol(const std::string& symbol)
  {

    // Validate uniqueness
    if (symbolSet.find(symbol) != symbolSet.end())
    {
      errorMessage =  "Party Symbol already exists. Please enter a different symbol.";
      return false;
    }
    // Validate the length of the symbol:
    // - Must be between 2 and 20 characters.
    if (symbol.length() < 2 || symbol.length() > 20)
    {
      errorMessage = "Invalid Party Symbol length.";
      return false;
    }

    // Validate the format of the symbol:
    // - Must consist only of alphabetic characters (A-Z, a-z).
    if (!std::all_of(symbol.begin(), symbol.end(), ::isalpha)) 
    {
      // error message about non-alphabetic characters.
      errorMessage =  "Invalid characters in Party Symbol. Only alphabets are allowed.";
      return false;
    }

    // If all validations pass, the symbol is considered valid.
    errorMessage = "";
    return true;
  }

  // Validates a region code based on its format and character composition.
  //
  // Args:
  //   code: The region code to validate.
  //
  // Returns:
  //   true if the code is valid, false otherwise.
  bool ElectionSystem::ValidateRegionCode(const std::string& code)
  {
    // Validate the format of the code:
    // - Length must be between 3 and 5 characters.
    // - Must contain at least one digit and one alphabetic character.
    // Ensure the presence of both a digit and an alphabetic character.
    if (std::none_of(code.begin(), code.end(), ::isdigit) ||
       std::none_of(code.begin(), code.end(), ::isalpha)) {
      // error message about the missing character types.
    errorMessage = "Region Code should contain at least one alpha and one numeric character.";
    return false;
  }

  // If all validations pass, the code is considered valid.
  errorMessage = "";
  return true;
  }

  
  // Determines whether a given string represents a valid non-negative integer.
  //
  // Args:
  //   str: The string to validate.
  //
  // Returns:
  //   true if the string is a valid non-negative integer, false otherwise.
  bool ElectionSystem::IsValidNumber(const std::string& str)
  {
    // Check for empty string:
    if (str.empty())
    {
      return false;  // Empty string is not a valid number.
    }

    // Ensure all characters are digits:
    for (char c : str)
    {
      if (!std::isdigit(c))
      {
        return false;  // Non-digit character found, invalid number.
      }
    }

    // Attempt conversion to integer and check for non-negative value:
    try 
    {
      int value = std::stoi(str);
      return value >= 0;  // Valid non-negative integer.
    } 
    catch (const std::exception& e) 
    {
      return false;  // Conversion failed, invalid number.
    }
  }

  
  // Converts a string to a non-negative integer, returning 0 on failure.
  //
  // Args:
  //   str: The string to convert.
  //
  // Returns:
  //   The converted non-negative integer value, or 0 if conversion fails.
  int ElectionSystem::Convert2Int(const std::string& str)
  {
    try
    {
      int value = std::stoi(str);  // Attempt to convert the string to an integer.
      // Ensure the value is non-negative:
      return value >= 0 ? value : 0;  // Return the value if non-negative, otherwise 0.
    } 
    catch (const std::exception& e)
    {
      // Conversion failed, return 0 to indicate an invalid or negative value.
      return 0;
    }
  }

    
// Validates candidate information from a CSV file and processes valid candidates.
//
// Returns:
//   true if at least one valid candidate was found, false otherwise.
bool ElectionSystem::CandidateCsvCheck() 
{
  std::ifstream inputFile("Candidate.csv");

  // Check if the file is open:
  if (!inputFile.is_open()) 
  {
    // Print a clear error message.
    std::cerr << "Error opening the Candidate file. Please ensure it exists and is accessible.\n";
    return false;
  }

  // Process each line in the CSV file:
  std::string line;
  while (std::getline(inputFile, line)) 
  {
    std::istringstream ss(line);
    std::string id, name, symbol, reg, count;

    // Extract fields from the line:
    std::getline(ss, id, ',');
    std::getline(ss, name, ',');
    std::getline(ss, symbol, ',');
    std::getline(ss, reg, ',');
    std::getline(ss, count, ',');

    // Handle missing fields:
    if (id.empty()) {
      // Skip lines with empty IDs as they are essential for validation.
      continue;
    }
    if (name.empty()) name = "";
    if (symbol.empty()) symbol = "";
    if (reg.empty()) reg = "";
    if (count.empty() || !IsValidNumber(count)) count = "0";  // Ensure valid count

    // Validate candidate information:
    if (ValidateCandidateID(id) && ValidateCandidateName(name) &&
        ValidatePartySymbol(symbol) && ValidateRegionCode(reg)) {
      // Create a valid Candidate object and store relevant data:
      Candidate candidate(id, name, symbol, reg, Convert2Int(count));
      validCandidateList.push_back(candidate);
      idSet.insert(id);  // Track unique IDs
      symbolSet.insert(symbol);  // Track unique symbols
      votesSet[id] = Convert2Int(count);  // Store vote counts
    } else {
      // Create an invalid Candidate object for reporting:
      Candidate candidate(id, name, symbol, reg, Convert2Int(count));
      invalidCandidateList.push_back(candidate);
    }
  }

  // Indicate success if at least one valid candidate was found:
  return validCandidateList.size() >= 1;
}

  
// Validates voter information from a CSV file and processes valid voters.
//
// Returns:
//   true if at least one valid voter was found, false otherwise.
bool ElectionSystem::VoterCsvCheck() 
{
  std::ifstream inputFile("Voter.csv");

  // Check if the file is open:
  if (!inputFile.is_open()) 
  {
    std::cerr << "Error opening the Voter file. Please ensure it exists and is accessible.\n";
    return false;
  }

  // Process each line in the CSV file:
  std::string line;
  while (std::getline(inputFile, line)) 
  {
    std::istringstream ss(line);
    std::string aadhar, status;

    // Extract Aadhar number and status from the line:
    if (std::getline(ss, aadhar, ',')) 
    {
      if (std::getline(ss, status, ',')) 
      {
        // Validate voter information:
        if (IsValidAadhar(aadhar) &&  // Ensure valid Aadhar format
            (checkAadhar.find(aadhar) == checkAadhar.end()) &&  // Check for duplicates
            IsValidStatus(status))  // Ensure valid status ("0" or "1")
        {  
          
            checkAadhar.insert(aadhar);  // Track unique Aadhar numbers
          bool voted = (status == "1");  // Convert status to boolean
          Voter v(aadhar, voted);  // Create a Voter object
          validVoterList.push_back(v);  // Add to valid voter list
        } 
        else {
          if(!aadhar.empty())
          invalidVoterList.emplace_back(aadhar, status);  // Add to invalid voter list
        }
      } else {
        // Handle missing status:
        if(!aadhar.empty())
        invalidVoterList.emplace_back(aadhar, "");  // Add with empty status
      }
    } 
    else {
      // Handle missing Aadhar number:
      // Skip the line as Aadhar is essential
    }
  }

  // Indicate success if at least one valid voter was found:
  return validVoterList.size() >= 1;
}

  
  
  bool ElectionSystem:: IsValidAadhar(const std::string& aadhar) {
    // Check if the string is a positive integer and has a length of 12
    if(aadhar[0] != '0' && aadhar.length() == 12 && std::all_of(aadhar.begin(), aadhar.end(), ::isdigit))
    {
      errorMessage = "";
      return true;
    }
    
    else
    { 
      errorMessage =  "Invalid Aadhar ID ";
      return false;;
    }
  }

 bool ElectionSystem:: IsValidStatus(const std::string& status) {
    // Check if the string is either "0" or "1" and has a length of 1
    if(status.length() == 1 && (status == "0" || status == "1"))
    {
      errorMessage = "";
      return true;
    }
    else
    {
      errorMessage = "Invalid Voting Status ";
      return false;;
    } 
 }
  
  // Repeatedly prompts the user to enter a valid integer choice.
  //
  // Returns:
  //   The valid integer entered by the user.
  int ElectionSystem:: GetChoice() 
  {
    while (true) // Loop until valid input is received
    {  
      std::cout << "Enter your choice: ";
      int choice{};
      std::cin >> choice;

      // Check for input failure:
      if (!std::cin) {
        if (std::cin.eof()) {  // If the input stream was closed
          exit(0);  // Terminate the program
        } else {  // Handle invalid input
          std::cin.clear();  // Reset the input stream
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
          std::cerr << "Oops, that input is invalid. Please try again.\n";
        }
      } else {  // Input is valid
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard any extra input
        return choice;  // Return the valid integer
      }
    }
  }

  
// Repeatedly prompts the user to enter a valid string for a given field.
//
// Args:
//   fieldName: The name of the field to prompt for.
//
// Returns:
//   The valid string entered by the user.
std::string ElectionSystem::GetValidString(const std::string& fieldName) {
  while (true) {  // Loop until valid input is received
    std::cout << "Enter " << fieldName << ": ";
    std::string input;
    std::getline(std::cin, input);

    // Check for input failure:
    if (!std::cin) {
      std::cin.clear();  // Reset the input stream
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
      std::cout << "Oops, there was an error. Please try again.\n";
    } else {  // Input is valid
      return input;  // Return the valid string
    }
  }
}


// Repeatedly prompts the user to enter a valid character for a given field.
//
// Args:
//   fieldName: The name of the field to prompt for.
//
// Returns:
//   The valid character entered by the user.
char ElectionSystem:: GetValidChar(const std::string& fieldName) {
  while (true) {  // Loop until valid input is received
    std::cout << "Enter " << fieldName << ": ";
    char input;
    std::cin >> input;

    // Check for input failure:
    if (std::cin.fail()) {
      std::cin.clear();  // Reset the input stream
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
      std::cout << "Oops, there was an error. Please try again.\n";
    } else {  // Input is valid
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard any extra input
      return input;  // Return the valid character
    }
  }
}


// Repeatedly prompts the user for admin credentials until successful or cancelled.
//
// Returns:
//   true if authentication is successful, false if the user cancels.
bool ElectionSystem::GetAdminAuthenicate() {
  while (true) {  // Loop until authentication or cancellation
    // Get valid username and password from user:
    std::string adminUsername="Admin Username ";
    std::string adminPassword="Admin Password ";
    std::string username = GetValidString(adminUsername);
    std::string password = GetValidString(adminPassword);

    // Check for successful authentication:
    if ( (adminValidate.find(username)!=adminValidate.end() && adminValidate[username] == password) ||  // Check stored credentials
        (username == "admin" && password == "admin")) {  // Check for default admin
      return true;  // Authentication successful
    } else {
      // Invalid credentials:
      std::cout << "Invalid Username or Password\n";
      std::cout << "Do you want to continue? (n for back)\n";
      std::string characterChoice = "a character";
      char result = GetValidChar(characterChoice);
      if (result == 'n') {
        return false;  // User cancelled
      }
    }
  }
}


// Gathers valid candidate information from the user and adds it to the validCandidateList.
//
// Returns:
//   true if a candidate was successfully added, false if the user cancelled.
bool ElectionSystem::AddCandidate() 
{
  std::string id, name, symbol, regionCode;

  // Get and validate candidate ID:
  while (true) {
    std::string candidateIdInput = "Candidate ID (only alphanumeric)";
    id = GetValidString(candidateIdInput);
    if (ValidateCandidateID(id)) {  // Ensure valid ID format and uniqueness
      
      break;
    } else {
      // Handle invalid ID:
      std::cerr << errorMessage << '\n';
      std::cout << "Do you want to continue ?  n for back \n";
      std::string characterChoice = "a character";
      char result = GetValidChar(characterChoice);
      if(result == 'n')  return false;  // Offer to try again or cancel
    }
  }

  // Get and validate candidate name:
  while (true) {
    std::string candidateNameInput = "Candidate Name (only alphabets )";
    name = GetValidString(candidateNameInput);
    if (ValidateCandidateName(name)) 
    {
      break;
    } 
    else 
    {
      // Handle invalid name:
      std::cerr << errorMessage << '\n';
      std::cout << "Do you want to continue ?  n for back \n";
      std::string characterChoice = "a character";
      char result = GetValidChar(characterChoice);
         if(result == 'n')
         { 
          // Store partial candidate info if cancelled
           Candidate candidate(id, "", "", "");
           invalidCandidateList.push_back(candidate);
           return false;
         }
    }
  }

  // Get and validate party symbol:
  while (true) {
    std::string partySymbolInput = "Party Symbol (only characters )";
    symbol = GetValidString(partySymbolInput);
    if (ValidatePartySymbol(symbol)) {  // Ensure valid symbol format and uniqueness
      
      break;
    } else {
      // Handle invalid symbol:
      std::cerr << errorMessage << '\n';
      std::cout << "Do you want to continue ?  n for back \n";
         std::string characterChoice = "a character";
         char result = GetValidChar(characterChoice);
         if(result == 'n')
         { 
           Candidate candidate(id, name, "", "");
           invalidCandidateList.push_back(candidate);
           return false;
         }
    }
  }

  // Get and validate region ID:
  while (true) {
    std::string regionIdInput = "Region ID (only alphanumeric)";
    regionCode = GetValidString(regionIdInput);
    if (ValidateRegionCode(regionCode)) {
      break;
    } else {
      // Handle invalid region ID:
      std::cerr << errorMessage << '\n';
      std::cout << "Do you want to continue ?  n for back \n";
         std::string characterChoice = "a character";
         char result = GetValidChar(characterChoice);
         if(result == 'n')
         { 
           Candidate candidate(id, name, symbol, "");
           invalidCandidateList.push_back(candidate);
           return false;
         }
    }
  }

  // Create and add the candidate:
  Candidate candidate(id, name, symbol, regionCode);
  symbolSet.insert(symbol);  // Track used symbols
  idSet.insert(id);  // Track used IDs
  validCandidateList.push_back(candidate);

  // Success message:
  std::cout << "Candidate Added Successfully\n";
  return true;
}

  
  
  // Identifies and guides the user to fill missing or invalid information in invalidCandidateList.
  //
  // Returns:
  //   true if candidates were successfully updated, false if the user cancelled.
  bool ElectionSystem::FillMissingCandidateInfo()
  {
      std::vector<Candidate> temp;  // Temporary storage for candidates with missing or invalid data
      
      // Identify candidates with missing or invalid data and fill in temp
      for(auto& candidate :invalidCandidateList)
      {
        std::string id = candidate.GetCandidateID();
        std::string name = candidate.GetCandidateName();
        std::string symbol = candidate.GetPartySymbol(); 
        std::string reg = candidate.GetRegion();
        if (id.empty()||name.empty()||symbol.empty()||reg.empty()|| !ValidateCandidateID(id)
        ||!ValidateCandidateName(name)
        ||!ValidatePartySymbol(symbol) 
        ||!ValidateRegionCode(reg))
        {
           temp.push_back(candidate);
        }
      }
      if(temp.size() >= 1)
      std::cout << "Fill missing data or update invalid data \n";
      else{
      std::cout << "No need to fill or to update invalid data \n";
      return false;;
      }
      while(true)
      {
       int count = 1;
       for (auto& candidate : temp) {
         std::cout << count << " Candidate ID: " << candidate.GetCandidateID()
                   << " Name: " << candidate.GetCandidateName()
                   << " Party Symbol: " << candidate.GetPartySymbol()
                   << " Region ID: " << candidate.GetRegion() << '\n';
                   count ++;
       }
       int candidateChoice =  {GetChoice()};
       if(candidateChoice >= 1&&candidateChoice < count )
       {
         Candidate& modify = temp[candidateChoice-1];
         std::string mid = modify.GetCandidateID();
         std::string mname = modify.GetCandidateName();
         std::string msymbol = modify.GetPartySymbol(); 
         std::string mreg = modify.GetRegion();
         int mcount = modify.GetNumOfVotes();

         
         
        //Candiadate ID 
        if (ValidateCandidateID(mid) )
        {
          
        }
        else
        {
          std::cerr << errorMessage << '\n';
          while(true)
          { 
              std::string newCandidateIdInput = "New Candidate ID (only alphanumeric) ";
              mid = GetValidString(newCandidateIdInput);
              if (ValidateCandidateID(mid) )
              {
                 idSet.insert(mid);
                 modify.SetCandidateID(mid);
                 //std::cout << "Candidate Information Updated Successfully \n";
                 break;
              }
              else
              {
                   std::cout << errorMessage << '\n';
                   std::cout << "Do you want to continue ?  n for back \n";
                   std::string characterChoice = "a character";
                   char result = GetValidChar(characterChoice);
                   if(result == 'n')
                    { 
                        return false;;
                    }
             }
          }
        }
        
        //Candidate Name
        if (ValidateCandidateName(mname) )
        {
          
          
        }
        else
        {
          std::cerr << errorMessage << '\n';
          while(true)
          { 
              std::string  newCandidateNameInput= "New Candidate Name (only characters ) ";
              mname = GetValidString(newCandidateNameInput);
              if (ValidateCandidateName(mname) )
              {
                 modify.SetCandidateName(mname);
                 //std::cout << "Candidate Information Updated Successfully \n";
                 break;
              }
              else
              {
                   std::cerr << errorMessage << '\n';
                   std::cout << "Do you want to continue ?  n for back \n";
                   std::string characterChoice = "a character";
                   char result = GetValidChar(characterChoice);
                   if(result == 'n')
                    { 
                        return false;;
                    }
             }
          }
        }
        
        //Candiadate Symbol
        if (ValidatePartySymbol(msymbol) )
        {
          
          
        }
        else
        {
          std::cerr << errorMessage << '\n';
          while(true)
          { 
              std::string newPartySymbolInput = "New Party Symbol (only characters ) ";
              msymbol = GetValidString(newPartySymbolInput);
              if (ValidatePartySymbol(msymbol) )
              {
                 //std::cout << "Candidate Information Updated Successfully \n";
                 symbolSet.insert(msymbol);
                 modify.SetPartySymbol(msymbol);
                 break;
              }
              else
              {
                   std::cerr << errorMessage << '\n';
                   std::cout << "Invalid Party Symbol \n";
                   std::cout << "Do you want to continue ?  n for back \n";
                   std::string characterChoice = "a character";
                   char result = GetValidChar(characterChoice);
                   if(result == 'n')
                    { 
                        return false;
                    }
             }
          }
        }
        
        if(ValidateRegionCode(mreg))
        {
         
        }
        else
        {
          std::cerr << errorMessage << '\n';
          while(true)
          { 
            std::string newRegionIdInput = "New Region ID (only alphanumeric) ";
            mreg = GetValidString(newRegionIdInput);
            if (ValidateRegionCode(mreg) )
            {
               
               break;
             }
             else
              {
                   std::cerr << errorMessage << '\n';
                   std::cout << "Invalid Region ID \n";
                   std::cout << "Do you want to continue ?  n for back \n";
                   std::string characterChoice = "a character";
                   char result = GetValidChar(characterChoice);
                   if(result == 'n')
                    { 
                        return false;
                    }
             }
           } 
         }
         Candidate candidate(mid, mname, msymbol, mreg,mcount);
         validCandidateList.push_back(candidate);
         temp.erase(temp.begin() + candidateChoice-1);
         invalidCandidateList.swap(temp);
         idSet.insert(mid);
         symbolSet.insert(msymbol);
         std::cout << "Candidate Information Updated Successfully \n";
         return true;
      }
      else 
      {
        std::cout << "Invalid Choice \n";
        std::cout << "Do you want to continue ?  n for back \n";
        std::string characterChoice = "a character";
        char result = GetValidChar(characterChoice);
        if(result == 'n')
        { 
           return false;
        }
      }
   }
  }
  
// Removes a candidate from the validCandidateList based on their ID.
//
// Returns:
//   true if a candidate was successfully removed, false if the user cancelled.
bool ElectionSystem::RemoveCandidate() {
  // Check for available candidates:
  if (validCandidateList.empty()) {
    std::cerr << "No candidates available to remove." << std::endl;
    return false;  // Exit if no candidates
  }

  // Display current candidate list:
  std::cout << "Candidate List:\n";
  for (const Candidate& candidate : validCandidateList) {
    std::cout << " Candidate ID: " << candidate.GetCandidateID()
              << " Name: " << candidate.GetCandidateName()
              << " Party Symbol: " << candidate.GetPartySymbol()
              << " Region ID: " << candidate.GetRegion() << '\n';
  }

  // Repeatedly prompt for candidate ID until a valid one is entered or user cancels:
  while (true) {
    // Prompt for candidate ID:
    std::string candidateID;
    std::cout << "Enter Candidate ID to remove: ";
    std::cin >> candidateID;

    // Find candidate in validCandidateList:
    auto it = std::find_if(validCandidateList.begin(), validCandidateList.end(),
                           [candidateID](const Candidate& candidate) {
                             return candidate.GetCandidateID() == candidateID;
                           });

    // Handle found or not found scenarios:
    if (it != validCandidateList.end()) {
      // Remove candidate and provide success message:
      validCandidateList.erase(it);
      votesSet.erase(candidateID);
      idSet.erase(candidateID);
      std::cout << "Candidate with ID: " << candidateID << " removed successfully!" << std::endl;
      return true;
    } else {
      // Handle not found scenario and prompt to continue:
      std::cout << "Candidate with ID: " << candidateID << " not found." << std::endl;
      std::cout << "Do you want to continue ?  n for back \n";
      std::string characterChoice = "a character";
         char result = GetValidChar(characterChoice);
      if(result == 'n')
      { 
        return false;
      }
    }
  }
}


  // Modifies a candidate's information in the validCandidateList.
  //
  // Returns:
  //   true if a candidate was successfully modified, false if the user cancelled.
  bool ElectionSystem::ModifyCandidate()
  {
      // Check for available candidates:
      if (validCandidateList.empty()) {
        std::cerr << "No candidates available to modify.\n";
        return false;;
       }
       // Display current candidate list for user reference:
       std::cout << "Candidate List \n";
       for (auto& candidate : validCandidateList) {
         std::cout  << " Candidate ID: " << candidate.GetCandidateID()
                   << " Name: " << candidate.GetCandidateName()
                   << " Party Symbol: " << candidate.GetPartySymbol()
                   << " Region ID: " << candidate.GetRegion() << '\n';
                
       }
       std::string candidateID;
       bool candidateFound = false;;
      // Repeatedly prompt for candidate ID until a valid one is entered or user cancels:
       while (!candidateFound) {
          std::string CandidateIdInput = "Candidate ID (only alphanumeric) ";
          candidateID = GetValidString(CandidateIdInput);
          // Find candidate in the list:
          auto it = std::find_if(validCandidateList.begin(), validCandidateList.end(), [candidateID](const Candidate& candidate) {
            return candidate.GetCandidateID() == candidateID; });

        if (it != validCandidateList.end()) {
            candidateFound = true;  // Candidate found
        } else {
        std::cout << "Candidate with ID: " << candidateID << " not found. Please enter a valid Candidate ID.\n";
        std::cout << "Do you want to continue ?  n for back \n";
        std::string characterChoice = "a character";
        char result = GetValidChar(characterChoice);
                if(result == 'n')
                { 
                    return false;  // Exit if user cancels
                 }
             }
       }

       // Candidate found, present modification options:
       std::cout << "Candidate found. Select the information to modify:\n";
       std::cout << "1. Name\n2. Party Symbol\n3. Region Code\n";
       while(true)
       {
        
        int choice {GetChoice()};
        switch (choice) {
        case 1: {
            std::string newName;
            //Getting New Candidate Name untill user cancels 
            while(true)
            { 
                 std::string NewCandidateNameInput ="New Candidate Name (only alphabets)";
                 newName = GetValidString(NewCandidateNameInput);
                 if (ValidateCandidateName(newName) )
                 {
                    break;
                 }
                 else
                 {
                  std::cerr << errorMessage << '\n';
                  std::cout << "Do you want to continue ?  n for back \n";
                  std::string characterChoice = "a character";
                  char result = GetValidChar(characterChoice);
                  if(result == 'n')
                  { 
                     return false; // Exit if user cancels
                  }
                 }
            }
            //Modify the Candidate Name 
            for (auto& candidate : validCandidateList) {
                if (candidate.GetCandidateID() == candidateID) {
                    candidate.SetCandidateName(newName);
                    std::cout << "Candidate Name updated successfully!\n";
                    break;
                }
            }
            return true;
        }
        case 2: {
            std::string newPartySymbol;
            //Getting New Party Symbol untill user cancels
            while(true)
            { 
                std::string NewPartySymbolInput = "New Party Symbol (only alphabets)";
                newPartySymbol = GetValidString(NewPartySymbolInput);
               if (ValidatePartySymbol(newPartySymbol) )
               {
                   
                   break;
               }
               else
                 {
                  std::cout << errorMessage << '\n';
                  std::cout << "Do you want to continue ?  n for back \n";
                  std::string characterChoice = "a character";
                  char result = GetValidChar(characterChoice);
                  if(result == 'n')
                  { 
                     return false; // Exit if user cancels
                  }
                 }
            }
            //Modify the Party Symbol 
            for (auto& candidate : validCandidateList) {
                if (candidate.GetCandidateID() == candidateID) {
                    candidate.SetPartySymbol(newPartySymbol);
                    symbolSet.insert(newPartySymbol);
                    std::cout << "Candidate Party Symbol updated successfully!\n";
                    break;
                }
            }
            return true;
        }
        case 3: {
            //Getting New RegionCode untill user cancels
            std::string newRegionCode;
            while(true)
            { 
               std::string NewRegionIdInput = "New Region ID (only alphanumeric)";
               newRegionCode = GetValidString(NewRegionIdInput);
               if (ValidateRegionCode(newRegionCode) )
               {
                  break;
               }
               else
                 {
                  std::cout << "Invalid Party Symbol \n";
                  std::cout << "Do you want to continue ?  n for back \n";
                  std::string characterChoice = "a character";
                  char result = GetValidChar(characterChoice);
                  if(result == 'n')
                  { 
                     return false;  // Exit if user cancels
                  }
                 }
                
            }
            //Modify the Region Code
            for (auto& candidate : validCandidateList) {
                if (candidate.GetCandidateID() == candidateID) {
                    candidate.SetRegion(newRegionCode);
                    std::cout << "Candidate Region Code updated successfully!\n";
                    break;
                }
            }
           return true;
        }
        
        default: {
            std::cout << "Invalid choice.\n";
            std::cout << "Do you want to continue ?  n for back \n";
            std::string characterChoice = "a character";
            char result = GetValidChar(characterChoice);
            if(result == 'n')
            { 
            return false; // Exit if user cancels
             }
             }
      }

    }
    return true;
  }

  // Adds a new voter to the validVoterList container.
  //
  // Returns:
  //   true if a voter was successfully added, false if the user cancelled.
  bool ElectionSystem::AddVoter()
  {
      // Variables for storing voter information:
      std::string aadhar,status;
      // Loops until a valid Aadhar number is entered or the user cancels:
      while(true)
      {
        // Prompts the user to enter the Aadhar number:
        std::cout << "Enter Aadhar Number (max 12 characters, numeric): ";
        std::getline(std::cin, aadhar);
        // Handles potential input failures:
        if (!std::cin) // if the previous extraction failed
        {
          if (std::cin.eof()) // if the stream was closed
          {
             exit(0); // shut down the program now
          }
          // let's handle the failure
          std::cin.clear();                           // put us back in 'normal' operation mode
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the bad input
          std::cout << "Oops, that input is invalid. Please try again.\n";
        }
        // Checks if the Aadhar number is valid:
        if(IsValidAadhar(aadhar))
        {
          // Checks if the Aadhar number is already present in checkAadhar:
          if(checkAadhar.find(aadhar) == checkAadhar.end())
          {
           checkAadhar.insert(aadhar); // Adds the Aadhar to checkAadhar
           break;
          }
          else
          {
           std::cout << "Aadhar Already Exist \n";
           std::cout << "Do you want to continue ?  n for back \n";
           std::string characterChoice = "a character";
           char result = GetValidChar(characterChoice);
           if(result == 'n')
           { 
            return false;  // Exits if the user doesn't want to continue
           }
          }
        }
        else
        {
          std::cout << errorMessage << "\n";
          std::cout << "Do you want to continue ?  n for back \n";
          std::string characterChoice = "a character";
          char result = GetValidChar(characterChoice);
          if(result == 'n')
          { 
           return false;  // Exits if the user doesn't want to continue
          }
        }
      }   
      // Creates a new Voter object with the entered Aadhar and default status:
      Voter v(aadhar,(bool) 0);
      validVoterList.push_back(v); // Adds the voter to the validVoterList
      std::cout << "Voter added successfully!" << std::endl;
      return true;  // Indicates successful voter addition
  }
 
 // Modifies the information of an existing voter in the validVoterList.
 //
 // Returns:
 //   true if a voter was successfully modified, false if the user cancelled.  
 bool ElectionSystem::ModifyVoter()
  {
     // Check for available voters:
     if (validVoterList.empty()) {
        std::cout << "No voters available to modify." << std::endl;
        return false;;
       }
     // Display a numbered list of voters:
     int count = 1;
     for (const auto& voter : validVoterList) {
      std::cout << count << " Aadhar ID " << voter.GetAadharID() << " Status " << voter.GetVotingStatus() << '\n';
      count++;
      }
      while(true)
      {
        int aadharIdChoice {GetChoice()};  // Prompt the user to select a voter by number:
        if(aadharIdChoice >= 1&&aadharIdChoice < count)
         {  
            auto& voter = validVoterList[aadharIdChoice-1];
             // Present modification options:
            std::cout << "1. Aadhar ID\n2. Voting Status\n";
            int updateChoice {GetChoice()};
            if(updateChoice == 1)
            { 
               std::string temp = voter.GetAadharID();
               auto it = checkAadhar.find(temp);
               checkAadhar.erase(it);
               std::string aadhar,status;
               while(true)
               {
                  std::cout << "Enter New Aadhar Number (max 12 characters, numeric): ";
                  std::getline(std::cin, aadhar);
                   if (!std::cin) // if the previous extraction failed
              {
                if (std::cin.eof()) // if the stream was closed
                {
                  exit(0); // shut down the program now
               }
              // let's handle the failure
              std::cin.clear();                           // put us back in 'normal' operation mode
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the bad input
              std::cout << "Oops, that input is invalid. Please try again.\n";
             }
             if(IsValidAadhar(aadhar))
             {
                if(checkAadhar.find(aadhar) == checkAadhar.end())
                {
                  checkAadhar.insert(aadhar);
                  voter.SetAadharID(aadhar);
                  std::cout << "Aadhar ID updated successfully!\n";
                  return true;
                  
                }
                else
                {
                  std::cout << "Aadhar Already Exist \n";
                  std::cout << "Do you want to continue ?  n for back \n";
                  std::string characterChoice = "a character";
                  char result = GetValidChar(characterChoice);
                  if(result == 'n')
                  { 
                     return false;
                  }
                }
            }
            else
            {
              std::cout << "Invalid Aadhar ID \n";
              std::cout << "Do you want to continue ?  n for back \n";
              std::string characterChoice = "a character";
              char result = GetValidChar(characterChoice);
                  if(result == 'n')
                  { 
                     return false;
                  }
            }
          }
        }
        else if(updateChoice == 2)
        { 
                std::string status;
                do {
                      std::cout << "Enter voting status (0 or 1) :";
                      std::getline(std::cin, status);
                      if (!std::cin) // if the previous extraction failed
  	              {
   	                if (std::cin.eof()) // if the stream was closed
   	           	{
   		           exit(0); // shut down the program now
   		        }
   	                // let's handle the failure
                       std::cin.clear();   // put us back in 'normal' operation mode
                       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the bad input
         	       std::cout << "Oops, that input is invalid. Please try again.\n";
  	              }
        } while (!IsValidStatus(status));
        bool res = (status == "1" ? 1 : 0);
        voter.SetVotingStatus(res); 
        std::cout << "Voting Status updated successfully!\n";
        return true;
        }   
         }
         else
         {
           std::cout << "Invalid Choice \n";
           std::cout << "Do you want to continue ?  n for back \n";
           std::string characterChoice = "a character";
           char result = GetValidChar(characterChoice);
           if(result == 'n')
           { 
           return false;;
           }
         }
       }
      return true; // Should not reach here, but compiler requires a return
  }
  

  // Removes a voter from the validVoterList and checkAadhar containers.
  //
  // Returns:
  //   true if a voter was successfully removed, false if the user cancelled.
  bool ElectionSystem::RemoveVoter()
  {

   // Check for available voters:
   if (validVoterList.empty()) {
        std::cout << "No voters available to remove." << std::endl;
        return false;;
    }
    // Prompt the user to enter the Aadhar ID of the voter to remove:
    std::string aadharID;
     while(true)
            {
              std::cout << "Enter Aadhar Number (max 12 characters, numeric): ";
              std::getline(std::cin, aadharID);
              if (!std::cin) // if the previous extraction failed
              {
                if (std::cin.eof()) // if the stream was closed
                {
                  exit(0); // shut down the program now
               }
              // let's handle the failure
              std::cin.clear();                           // put us back in 'normal' operation mode
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the bad input
              std::cout << "Oops, that input is invalid. Please try again.\n";
             }
             if(IsValidAadhar(aadharID))
             {
              break;
             }
             else
             {
              std::cout << "Invalid Aadhar ID \n";
              std::cout << "Do you want to continue ?  n for back \n";
                  std::string characterChoice = "a character";
                  char result = GetValidChar(characterChoice);
                  if(result == 'n')
                  { 
                     return false;
                  }
             }
           }   
        // Find the voter with the matching Aadhar ID:
        auto it = std::find_if(validVoterList.begin(), validVoterList.end(), [aadharID](Voter& voter) {
            return voter.GetAadharID() == aadharID;
        });
        // Remove the voter if found:
        if (it != validVoterList.end()) {
            auto it1 = checkAadhar.find(aadharID);
            checkAadhar.erase(it1);   // Remove from Aadhar set
            validVoterList.erase(it);  // Remove from voter list
            std::cout << "Voter with Aadhar ID " << aadharID << " removed successfully!" << std::endl;
        } else {
            std::cout << "Voter with Aadhar ID " << aadharID << " not found." << std::endl;
        }
      return true;
    }
  
// Casts a vote for the specified candidate and updates the voter's status.
//
// Returns:
//   true if a vote was successfully cast, false if the user cancelled or an error occurred
bool ElectionSystem::CastVote()
{
  // Display a list of candidates:
  for(auto& candidate : validCandidateList)
  {
    std::cout << "Candidate ID : " << candidate.GetCandidateID() << "  Candidate Name  : " << candidate.GetCandidateName() <<" Candidate Symbol : " << candidate.GetPartySymbol() << "   Candidate Region : " << candidate.GetRegion() << '\n';
  }
  
  // Prompt the user to enter a valid candidate ID and Aadhar ID:
   bool candidateFlag = false, aadharFlag = false;
   std::string candidateID,aadhaarID;
   
   while(true)
   {
   
   std::cout<<"Enter Candidate ID :";
   std::cin>> candidateID;
   if (!std::cin) // if the previous extraction failed
   {
            if (std::cin.eof()) // if the stream was closed
            {
                exit(0); // shut down the program now
            }
            // let's handle the failure
            std::cin.clear();                           // put us back in 'normal' operation mode
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the bad input
            std::cout << "Oops, that input is invalid. Please try again.\n";
   }
   else
   {
    auto it = idSet.find(candidateID);
    if(it == idSet.end())
    {
      std::cout << "Entered Candidate ID Not Exisiting \n";
      std::cout << "Do you want to continue ?  n for back \n";
     std::string characterChoice = "a character";
     char result = GetValidChar(characterChoice);
     if(result == 'n')
     { 
      return false;;
      }           
    }
    else
    {
      candidateFlag = true;
      break;
    }
   }
  }
  
  while(true)
   {
   
   std::cout<<"Enter Aadhar ID :";
   std::cin>> aadhaarID;;
   if (!std::cin) // if the previous extraction failed
   {
            if (std::cin.eof()) // if the stream was closed
            {
                exit(0); // shut down the program now
            }
            // let's handle the failure
            std::cin.clear();                           // put us back in 'normal' operation mode
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the bad input
            std::cout << "Oops, that input is invalid. Please try again.\n";
   }
   else
   {
    auto it = checkAadhar.find(aadhaarID);
    if(it == checkAadhar.end())
    {
      std::cout << "Entered Aadhar ID Not Exisiting \n"; 
      std::cout << "Do you want to continue ?  n for back \n";
      std::string characterChoice = "a character";
         char result = GetValidChar(characterChoice);
      if(result == 'n')
      { 
        return false;;
      }
    }
    else
    {
      aadharFlag = true;
      break;
    }
   }
  }

  bool currentStatus;
  for (auto& voter: validVoterList) {
        if (voter.GetAadharID() == aadhaarID) {
             currentStatus = voter.GetVotingStatus();
          }
    }
  // Check if the voter has already voted:
  if(!currentStatus)
  {
   // Find the selected candidate and increment their vote count:
   if(aadharFlag &&  candidateFlag)
   {
     for (Candidate& candidate : validCandidateList) {
         if (candidate.GetCandidateID() == candidateID) {
             // Increment the vote count for the selected candidate
             votesSet[candidate.GetCandidateID()]++;
             candidate.SetVotes(votesSet[candidate.GetCandidateID()]);
             // Mark the voter as having voted:
             for (auto& voter:validVoterList) {
        	if (voter.GetAadharID() == aadhaarID) {
             	    voter.SetVotingStatus(true);
             	    std::cout << "Vote cast successfully for Candidate ID: " << candidateID << '\n';
             	    break;
         	 }
    	     }
             break;
         }
     }
   }
  }
  else
  {
    std::cout << "Voter Already Voted \n";
  }
      return true;
    }
  
  // Displays the vote count for a specific candidate.
  //
  // Returns:
  //   true if the result was displayed successfully, false if the user cancelled or an error occurred.
  bool ElectionSystem::IndividualResult()
  {
   std::string candidateID;
   // Get the candidate ID from the user:
   while(true)
   {
   
   std::cout<<"Enter Candidate ID : ";
   std::cin>> candidateID;
   if (!std::cin) // if the previous extraction failed
   {
            if (std::cin.eof()) // if the stream was closed
            {
                exit(0); // shut down the program now
            }
            // let's handle the failure
            std::cin.clear();                           // put us back in 'normal' operation mode
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the bad input
            std::cout << "Oops, that input is invalid. Please try again.\n";
   }
   else
   {
    auto it = idSet.find(candidateID);
    if(it == idSet.end())
    {
      std::cout << "Enter Candidate ID Not Exisiting \n"; 
      std::cout << "Do you want to continue ?  n for back \n";
         std::string characterChoice = "a character";
         char result = GetValidChar(characterChoice);
                  if(result == 'n')
                  { 
                     return false;;
                  }          
    }
    else
    {
      break;
    }
   }
  }
  // Display the vote count for the candidate:
  std::cout << "Candidate ID: " << candidateID << ", Vote Count: " << votesSet[candidateID] << std::endl;
  
      return true;
    }
  

  // Displays the overall election results in descending order of vote count.
  //
  // Returns:
  //   true if the results were displayed successfully
  bool ElectionSystem::ShowResult()
  {
     // Update the vote counts from the candidate list:
      for (auto& candidate : validCandidateList) {
         votesSet[candidate.GetCandidateID()] = candidate.GetNumOfVotes();
                
       }
      // Convert the map to a vector of pairs
      std::vector<std::pair<std::string, int64_t>> sortedVotes(votesSet.begin(), votesSet.end());

      // Sort the vector based on values (second element of the pair)
      std::sort(sortedVotes.begin(), sortedVotes.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // descending order
      });

     // Print the sorted vector
    for (const auto& pair : sortedVotes) {
        std::cout << pair.first << " has " << pair.second << " votes \n";
       } 
      return true;
    }

  // Attempts to fill missing or correct invalid voter information.
  //
  // Returns:
  //   true if the information was updated successfully, false if the user cancelled or an error occurred. 
  bool ElectionSystem::FillMissingVoterInfo()
  { 

      if(invalidVoterList.empty())
      { 
         std::cout << "There is no Invalid data \n";
         return true; 
      }
      std::cout << "Fill missing data or update invalid data \n";
      int count = 1;
      for (const auto& pair :invalidVoterList) {
        std::cout << count << " Aadhar ID " << pair.first << " Status " << pair.second << '\n';
        count++;
      }
      while(true)
      {
        int aadharIdChoice {GetChoice()};
        if(aadharIdChoice >= 1 && aadharIdChoice <= count)
         {  
             
            auto pair =invalidVoterList[aadharIdChoice-1];
            std::string aadhar = pair.first;
            std::string status = pair.second;
            bool flag1 = false, flag2 = false;;
            if(IsValidAadhar(aadhar) && (checkAadhar.find(aadhar) == checkAadhar.end()))
            {
                  flag1 = true;
                  checkAadhar.insert(aadhar);
            }
            else
            {
              while(true)
               {
                  std::cout << "Enter New Aadhar Number (max 12 characters, numeric): ";
                  std::getline(std::cin, aadhar);
                   if (!std::cin) // if the previous extraction failed
                   {
                      if (std::cin.eof()) // if the stream was closed
                      {
                          exit(0); // shut down the program now
                       }
                     // let's handle the failure
                      std::cin.clear();                           // put us back in 'normal' operation mode
                      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the bad input
                       std::cout << "Oops, that input is invalid. Please try again.\n";
                   }
                   if(IsValidAadhar(aadhar))
                   {
                     if(checkAadhar.find(aadhar) == checkAadhar.end())
                     {
                        checkAadhar.insert(aadhar);
                        flag1 =true;
                        break;
                     }
                     else
                     {
                        std::cout << "Aadhar Already Exist \n";
                        std::cout << "Do you want to continue ?  n for back \n";
                         std::string characterChoice = "a character";
                         char result = GetValidChar(characterChoice);
                         if(result == 'n')
                          { 
                             return false;;
                          }
                     }
                   }
                   else
                   {
                     std::cout << "Invalid Aadhar ID \n";
                     std::cout << "Do you want to continue ?  n for back \n";
                  std::string characterChoice = "a character";
                  char result = GetValidChar(characterChoice);
                  if(result == 'n')
                  { 
                     return false;
                  }
                  
                  }
                 }
             }
             
             if(IsValidStatus(status))
             {
                flag2 = true;
             }
             else
             {
              
               while(true)
               {
                   std::cout << "Enter voting status (0 or 1):";
                   std::getline(std::cin, status);
                   if (!std::cin) // if the previous extraction failed
  	           {
   	            if (std::cin.eof()) // if the stream was closed
   		    {
   		       exit(0); // shut down the program now
   		     }
   	             // let's handle the failure
                     std::cin.clear();   // put us back in 'normal' operation mode
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the bad input
         	     std::cout << "Oops, that input is invalid. Please try again.\n";
  	           }
  	           if(IsValidStatus(status))
  	           {
  	                flag2 = true;
  	                break;
   	           }
   	           else
   	           {
   	             std::cout << "Invalid Status \n";
   	             std::cout << "Do you want to continue ?  n for back \n";
                  std::string characterChoice = "a character";
         char result = GetValidChar(characterChoice);
                  if(result == 'n')
                  { 
                     return false;;
                  }
                  
                  }
  	      }
  	      
  	    }
               
          
            if(flag1 && flag2)
            {  
               bool res = (status == "1" ? 1 : 0); 
               Voter v(aadhar,(bool) res);
               validVoterList.push_back(v);
               invalidVoterList.erase(invalidVoterList.begin() + aadharIdChoice - 1);
               std:: cout << "Voter Information Updated Successfully \n";
               return true;
            }

            
         }
         else
         {
           std::cout << "Invalid Choice ";
           std::cout << "Do you want to continue ?  n for back \n";
                  std::string characterChoice = "a character";
         char result = GetValidChar(characterChoice);
                  if(result == 'n')
                  { 
                     return false;
                  }
         }
         
      }
      
      return true;
    }
  
  // Writes the valid voter data to a CSV file
  void ElectionSystem::WriteVoterDataToCSV() {
    std::ofstream outputFile("Voter.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the output voter file.\n";
        return ;
    }

    // Write the voter data:
    for (const auto& voter : validVoterList) {
        outputFile << voter.GetAadharID() << ","
                   << voter.GetVotingStatus() << "\n";
    }

    outputFile.close();
   }


   // Writes the valid candidate data to a CSV file
   void ElectionSystem::WriteCandidateDataToCSV() {
    std::ofstream outputFile("Candidate.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the output candidate file.\n";
        return;
    }

    // Write the candidate data:
    for (const auto& candidate : validCandidateList) {
        outputFile << candidate.GetCandidateID() << ","
                   << candidate.GetCandidateName() << ","
                   << candidate.GetPartySymbol() << ","
                   << candidate.GetRegion() << "," 
                   << candidate.GetNumOfVotes() << "\n";
    }

    outputFile.close();
   }

   void ElectionSystem::WriteResultDataToCSV() {
    std::ofstream outputFile("result.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the result file.\n";
        return;
    }
    std::vector<std::pair<std::string, int64_t>> sortedVotes(votesSet.begin(), votesSet.end());

      // Sort the vector based on values (second element of the pair)
      std::sort(sortedVotes.begin(), sortedVotes.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // descending order
      });
       
    // Iterate through the map and write data to the CSV file
    for (const auto& entry : sortedVotes) {
        outputFile << entry.first << "," << entry.second << std::endl;
    }

    outputFile.close();
  }

  // Destructor for the ElectionSystem class.
// Writes election results, voter data, and candidate data to CSV files.
  ElectionSystem::~ElectionSystem()
 {
   // Write election results to CSV
   ElectionSystem::WriteResultDataToCSV();

   // Write voter data to CSV:
   ElectionSystem::WriteVoterDataToCSV();

   // Write candidate data to CSV:
   ElectionSystem::WriteCandidateDataToCSV();
 }
 
 // Checks if there are enough valid voters and candidates to conduct an election.
//
// Returns:
//   true if there's at least one valid voter and one valid candidate, false otherwise.
 bool ElectionSystem::checkCast()
 {
   return validVoterList.size() >= 1 && validCandidateList.size() >= 1;
 }

// Checks if there are  candidates to show result.
//
// Returns:
//   true if there's at least one valid candidate, false otherwise.
  bool ElectionSystem::checkCandidate()
 {
   return validCandidateList.size() >= 1;
 }


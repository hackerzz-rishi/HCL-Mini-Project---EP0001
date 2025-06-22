# Election Management System

This project is a console-based Election Management System written in C++. It allows administrators to manage candidates and voters, and enables voters to cast votes. The system ensures data integrity through validation and stores all data in CSV files.

## Features

- **Admin Authentication:** Secure login for administrators using credentials stored in `Admin.csv`.
- **Candidate Management:** Add, modify, remove, and validate candidates. Candidate data is stored in `Candidate.csv`.
- **Voter Management:** Add, modify, remove, and validate voters. Voter data is stored in `Voter.csv`.
- **Voting:** Registered voters can cast votes for valid candidates.
- **Result Display:** View overall and individual candidate results. Results are stored in `result.csv`.
- **Data Validation:** Ensures unique IDs, correct formats, and prevents duplicate entries.

## File Structure

- `main.cpp` - Entry point of the application.
- `election.h` / `election.cpp` - Core logic for managing the election process.
- `candidate.h` / `candidate.cpp` - Candidate class and related logic.
- `voter.h` / `voter.cpp` - Voter class and related logic.
- `Admin.csv` - Stores admin credentials.
- `Candidate.csv` - Stores candidate information.
- `Voter.csv` - Stores voter information.
- `result.csv` - Stores election results.

## How to Build

1. Ensure you have a C++ compiler (e.g., g++) installed.
2. Compile all `.cpp` files together:

   ```sh
   g++ main.cpp election.cpp candidate.cpp voter.cpp -o election_system
   ```

3. Run the program:

   ```sh
   ./election_system
   ```

## Usage

1. On startup, the main menu offers options for admin login, casting votes, and viewing results.
2. Admins can manage candidates and voters after successful authentication.
3. Voters can cast their vote using their Aadhaar ID.
4. Results can be viewed at any time.

## Data Files

- **Admin.csv:**  
  Format: `username,password,checksum`
- **Candidate.csv:**  
  Format: `candidate_id,name,symbol,region_id,votes`
- **Voter.csv:**  
  Format: `aadhaar_id,voting_status` (1 = voted, 0 = not voted)
- **result.csv:**  
  Format: `candidate_id,votes`

## Notes

- Ensure all CSV files are present in the working directory.
- The system performs input validation and will prompt for corrections if invalid data is entered.


## Acknowledgments

- Inspired by real-world election processes.
- Built as a mini-project for educational purposes.
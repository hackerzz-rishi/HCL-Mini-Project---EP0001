#include "election.h"
// Main function that drives the Election Management System.
int main()
{

 // Create an instance of the ElectionSystem class:
 ElectionSystem e;

 // Check for necessary files and data: 
 bool adminOption = e.AdminCsvCheck() || true;
 bool candidateCast = e.CandidateCsvCheck();
 bool voterCast = e.VoterCsvCheck();
 bool castOption = candidateCast & voterCast;
 bool software = true;


 while(software)
 {
   // Display main menu:
   std::cout << "Welcome to the Election Management System!" << std::endl;
   std::cout << "Choose an option:\n";
   std::cout << "1. Enter as Admin\n";
   std::cout << "2. Cast Vote\n";
   std::cout << "3. Show Results\n";
   std::cout << "4. View Individual Results\n";
   std::cout << "5. Exit\n";
   int choice {e.GetChoice()};

   switch(choice)
   {

     case 1:
     { 
       //Check for Admin Option
       if(adminOption)
       {
         //Check Admin Credentials
         bool adminAuthenticate = e.GetAdminAuthenicate();
         while (adminAuthenticate) 
         {
            // Admin options:
            std::cout << "Admin Options:\n";
            std::cout << "1. Candidate Registration\n";
            std::cout << "2. Fill missing informations of candidates\n";
            std::cout << "3. Modify Candidate Details\n";
            std::cout << "4. Remove Candidate\n";
            std::cout << "5. Add Voter\n";
            std::cout << "6. Fill missing informations of voters\n";
            std::cout << "7. Modify Voter Details\n";
            std::cout << "8. Remove Voter\n";
            std::cout << "9. Back to Main Menu\n";
            int adminChoice {e.GetChoice() };
            switch(adminChoice)
            {
              case 1: 
              {
                std::cout << "Register Candidate \n" ; 
                e.AddCandidate();
                break;
              }
              case 2: 
              {
                std::cout << "Fill Missing Candidate \n" ;
                e.FillMissingCandidateInfo();
                break;
              }
              case 3: 
              {
                std::cout << "Modify  Candidate \n";
                e.ModifyCandidate();
                break;
              }
              case 4: 
              {
                std:: cout << "Remove Candidate \n";
                e.RemoveCandidate();
                break;
              }
              case 5: 
              {
                std::cout << "Add Voter \n";
                e.AddVoter();
                break;
              }
              case 6:
              {
                std::cout << "Fill Missing Voter \n" ;
                e.FillMissingVoterInfo();
                break;
              }
              case 7: 
              {
                std::cout << "Modify Voter \n";
                e.ModifyVoter();
                break;
              }
              case 8: 
              {
                std::cout << "Remove Voter \n";
                e.RemoveVoter();  
                break;
              }
              case 9: 
              {
                // Exit the Admin Option
                adminAuthenticate = false;;
                break;
              }
              default: 
              {
                // Invalid choice:
                std::cout << "Invalid choice. Please try again.\n";
              }
           }
         }
      }
       else
       std::cout << "There is no Admin to access Admin Option\n";
       break;
    }
    case 2:
    { 
      // Check to Cast vote 
      if(e.checkCast())
      {
      std::cout << "Cast Vote \n";
      // Cast Vote
      e.CastVote();  
      }
      else
      {
        std::cout << "There is no Candidate or Voter to Cast Vote \n";
      }
      break;
    }
    
    case 3:
    {
      // Check to Show results
      if(e.checkCandidate())
      {
      std::cout << "Show Result \n";
      // Show Results
      e.ShowResult();
      }
      else
      {
        std::cout << "There is no Candidate to Show Result \n";
      }
      break;
    }
    case 4:
    { 
      // Check to Show Individual Results
      if(e.checkCandidate())
      {
      std::cout << "Individual Result \n";
      // View individual results:
      e.IndividualResult();
      }
      else
      {
        std::cout << "There is no Candidate to Individual Result \n";
      }
      
      break;
    } 
    case 5:
    {
      // Exit the program:
      software = false;;
      break;
    }
    default:
    {
      // Invalid choice:
      std::cout << "Invalid choice. Please try again.\n";
    }
  }
 }
 return 0;
}


### Issue report of Microsoft MPI (https://docs.microsoft.com/en-us/message-passing-interface/microsoft-mpi)

#### open a power shell terminal 
#### cd [root path]\MicrosoftMPI\Bin>
#### Run " .\mpiexec.exe -n [Number of Processes] ..\..\Issues\IssueReport\Debug\IssueReport.exe"


#### Issue 1:
##### MPI_Alltoallv Function occasionally freezes using MPI_THREAD_MULTIPLE mode.
#### Test scenario and findings:
##### O(passed)  number of processes: 1	number of threads for each: 5
##### O(passed)  number of processes: 2	number of threads for each: 5
##### X(failed)  number of processes: 3	number of threads for each: 5
##### X(failed)  number of processes: 4	number of threads for each: 5
##### X(failed)  number of processes: 5	number of threads for each: 5
##### O(passed)  number of processes: 9 number of threads for each: 5
##### O(passed)  number of processes: 10 number of threads for each: 5
##### *X(failed) just indicates that it did happent to freeze within 5 minutes.
##### *O(passed) just indicates that it did NOT happent to freeze running more than 5 minutes.

#### findings 1: less number or more number of processes could survive longer in this test.
#### findings 2: number of processes as "3" frozed first in this test.

#### Test Environment:
##### -- Windows 10
##### -- Visual Studio 2019 (v142)
##### -- Microsoft .NET Framework (4.8.03752)
##### -- ISO C++14 Standard (/std:c++14)


### How to install MSMPI
#### Download (https://www.microsoft.com/en-us/download/details.aspx?id=100593)
#### Install both msmpisetup.exe and msmpisdk.msi

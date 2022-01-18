#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <signal.h>
#include <string>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace Lab1_OS_Namespace {

	class myProcess {
		std::string nameOfProcess;
		pid_t processPID;
	private:
		myProcess() { nameOfProcess = "-"; }
		myProcess(std::string nameOfProcess) { this->nameOfProcess = nameOfProcess; }
		void setNameOfProcess(std::string nameOfProcess) { this->nameOfProcess = nameOfProcess; }
		std::string getNameOfProcess() { return nameOfProcess; }

		void run() {
			this->processPID = fork();
			if (this->processPID == -1) {
				perror("FORK");
				exit(EXIT_FAILURE);
			}
		}

		void finish() { ::kill(this->processPID, SIGTERM); }

		bool isActive() {
			if (this->processPID) return false;
			else return true;
		}
	};

	class Manager {
		myProcess funcF;
		myProcess funcG;
		int x;
	public:

		Manager() {
			this->funcF.setNameOfTheProcess("../f");
			this->funcG.setNameOfTheProcess("../g");
			x = input();
		}

		void run() {
			this->funcG.run();
			pid_t funcF1;
			pid_t funcG1;

			if (!(funcF1 = fork())) {
				char* arg_list[] = { funcF.getNameOfTheProcess().data(), nullptr };
				execve(funcF.getNameOfTheProcess.c_str(), arg_list, nullptr);
				perror("EXECVE");
				exit(EXIT_FAILURE);
			}
			else {
				unlink("_f")
			}
		}
		
		template<typename T>
		bool is_hard_fail(T) { return false; }

		void createFO(std::string nameOfTheProcess) {
			unlink(nameOfTheProcess.c_str());
			if (mkfifo(nameOfTheProcess.c_str(), 1000) == -1)
				std::cout << "Can't create a fifo" << std::endl;
		}

		void enterFO(int fo) {
			if (write(fo, &x, sizeof(int)) == -1)
				std::cout << "Can't write a fifo" << std::endl;
		}
		
		int input() {
			std::cout << "Please, type x: " << std::endl;
			int x;
			std::cin >> x;
			return x;
		}
	};

	volatile sig_atomic_t shutFlag = 1;
	void Q(int shutFlagN) { shutFlag = 0; }
	int main() {
		signal(SIGTERM, Q);
		int fun = open("fof", O_RDONLY);
		int x;
		if (read(fun, &x, sizeof(int)) == -1) {
			std::cout << "can't read fifo" << std::endl;
			return 2;
		}
		close(fun);
		std::cout << os::lab1::compfuncs::trial_f<os::lab1::compfuncs::INT_SUM>(x);
		int fo;
		fo = open("ffoB", O_WRONLY);
		if (std::holds_alternative<os::lab1::compfuncs::hard_fail>(os::lab1::compfuncs::trial_f<os::lab1::compfuncs::INT_SUM>(x))) {
			std::string hardFAIL = "hard fail in f function";
			if (write(fo, hardFAIL.c_str(), strlen(hardFAIL.c_str())) = -1) {
				std::cout << "error to write" << std::endl;
				return 2;
			}
			return 2;
		}
		else {
			auto y = os::lab1::compfuncs::trial_f<os::lab1::compfuncs::INT_SUM>(x);
			if (write(fo, &y, sizeof(y)) == -1) {
				std::cout << "Error to write" << std::endl;
			}
		}
		close(fof);
		exit(EXIT_SUCCESS);
	}
	shutFlag = 1;
	int main() {
		signal(SIGTERM, Q);
		int fun = open("fog", O_RDONLY);
		int x;
		if (read(fun, &x, sizeof(int)) == -1) {
			std::cout << "can't read fifo" << std::endl;
			return 2;
		}
		close(fun);
		std::cout << os::lab1::compfuncs::trial_f<os::lab1::compfuncs::INT_SUM>(x);
		int fo;
		fo = open("gfoB", O_WRONLY);
		if (std::holds_alternative<os::lab1::compfuncs::hard_fail>(os::lab1::compfuncs::trial_f<os::lab1::compfuncs::INT_SUM>(x))) 
			raise(SIGTERM);
		else {
			auto y = os::lab1::compfuncs::trial_f<os::lab1::compfuncs::INT_SUM>(x);
			if (write(fo, &y, sizeof(y)) == -1) {
				std::cout << "Error to write" << std::endl;
			}
		}
		close(fog);
		exit(EXIT_SUCCESS);
	}
}

int main() {
	Lab1_OS_Namespace::Manager programm;
	programm.run();
	return 0;
}
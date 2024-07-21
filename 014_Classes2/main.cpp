#include <iostream>

class Log {
public:
	static const int LogLevelInfo = 0;
	static const int LogLevelWarning = 1;
	static const int LogLevelError = 2;

private:
	int m_level = LogLevelInfo;
public:

	void Set_Level(int level) {
		m_level = level;
	}

	void Status() {

		switch (m_level) {
			case LogLevelError:
				if (LogLevelError >= m_level)
					std::cout <<"Error" << std::endl;
				break;

			case LogLevelWarning:
				if (LogLevelWarning >= m_level)
					std::cout << "Warning" << std::endl;
				break;

			case LogLevelInfo:
				if (LogLevelInfo >= m_level)
					std::cout << "Info" << std::endl;
				break;
		}
	}

	void Error(const char* message) {
		if (LogLevelError >= m_level)
			std::cout << message << std::endl;
	}

	void Warn(const char* message) {
		if (LogLevelWarning >= m_level)
			std::cout << message << std::endl;
	}

	void Info(const char* message) {
		if (LogLevelInfo >= m_level)
			std::cout << message << std::endl;
	}
};

int main() {
	Log log;
	log.Set_Level(log.LogLevelWarning);

	std::cout << "Status" << std::endl;
	log.Status();

	std::cout << "\nDebugging using LogLevel" << std::endl;
	log.Error("Hello Error");
	log.Warn("Hello Warn");
	log.Info("Hello Info");
}
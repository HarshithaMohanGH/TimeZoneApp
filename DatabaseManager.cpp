#include "DatabaseManager.h"

void DatabaseManager::dbLogInteraction(const string& interaction, const string& time){
	try {
		conn->setSchema("global_time_zone");

		PreparedStatement* pstmt = conn->prepareStatement(
			"INSERT INTO user_interactions (timestamp, interaction) VALUES (?, ?)"
		);
		pstmt->setString(1, time); // Implement getCurrentTimestamp() function
		pstmt->setString(2, interaction);
		pstmt->executeUpdate();

		delete pstmt;
	}
	catch (const SQLException& e) {
		cerr << "Error: " << e.what() << endl;
	}
}

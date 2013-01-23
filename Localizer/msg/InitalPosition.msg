#A message for describing the intial position of the robot during localization
#The localizer will take in the side and distance from the FeatureFinder and 
#determine the inital position of the robot

bool right #side 1 for right side and 0 for left side
bool distance #euclidean distance from the center feature on right or left side
int32 x
int32 y
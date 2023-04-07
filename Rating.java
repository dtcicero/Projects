
public class Rating {
	private int score;
	private User user;
	
	public Rating(User newUser, int newScore) {
		user = newUser;
		if (newScore == 1 || newScore == 0 || newScore == -1)
		{
			score = newScore;
			
		}
		else { score = 0; }
	}
	
	@Override
	public String toString() {
		String toReturn = "Rating was ";
		
		if (score == 1) toReturn += "an upvote";
		else if (score == 0) toReturn += "a pass";
		else if (score == -1) toReturn += "a downvote";
		
		return toReturn;
		
	}
	
	@Override
	public boolean equals(Object obj) {
		if (this.getClass() == obj.getClass()) {
			Rating newRating = (Rating) obj;
			if (this.getUser() == newRating.getUser() &&
				this.getScore() == newRating.getScore())
				return true;
		}
		return false;
	}
	
	public int getScore() {
		return score;
	}
	
	public User getUser() {
		return user;
	}
	
	public boolean setScore(int sco) {
		if (sco == 1 || sco == 0 || sco == -1)
		{
			score = sco;
			return true;
		}
		return false;
	}
	
	public void setUser(User use)
	{
		user = use;
	}
}

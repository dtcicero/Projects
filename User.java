import java.util.ArrayList;

public class User {
	private String userName;
	private ArrayList<Meme> memesCreated;
	private ArrayList<Meme> memesViewed;
	
	public User(String name) {
		userName = name;
		memesViewed = new ArrayList<Meme>();
		memesCreated = new ArrayList<Meme>();
	}
	
	public void rateMeme(Meme meme, int rate) {
		memesViewed.add(meme);
		meme.addRating(new Rating(this, rate));
	}
	
	public Meme createMeme(BackgroundImage pic, String cap) {
		Meme meme = new Meme(pic, cap, this);
		memesCreated.add(meme);
		return meme;
	}
	
	public boolean deleteMeme(Meme meme) {
		if (memesCreated != null && memesCreated.contains(meme) && meme.getShared() == false) {
			memesCreated.remove(meme);
			return true;
		}
		return false;
	}
	
	public void shareMeme(Meme meme, Feed feed) {
		meme.setShared(true);
		feed.getMemes().add(meme);
	}
	
	public boolean rateNextMemeFromFeed(Feed feed, int score) {
		Meme newMeme = feed.getNewMeme(this);
		if (newMeme == null) return false;
		memesViewed.add(newMeme);
		newMeme.addRating(new Rating(this, score));
		return true;
		
	}
	
	public double calculateReputation() {
		double sum = 0;
		int count = 0;
		if (memesCreated == null) {
			return 0.0;
		}
		else {
			for (Meme i : memesCreated) {
				sum += i.calculateOverallRating();
				count++;
			}
		}
		if (count == 0) return 0;
		return sum / count;
	}
	
	@Override
	public String toString() {
		String toReturn = "";
		toReturn += userName + " has rated (" + memesViewed.size() + ") memes, (" + calculateReputation() + ")";
		return toReturn;
	}
	
	@Override
	public boolean equals(Object obj) {
		if (this.getClass() == obj.getClass()) {
			User newUser = (User) obj;
			if (this.getUserName() == newUser.getUserName())
				return true;
		}
		return false;
	}
	
	public String getUserName() {
		return userName;
	}
	
	public ArrayList<Meme> getMemesCreated(){
		return memesCreated;
	}
	
	public ArrayList<Meme> getMemesViewed(){
		return memesViewed;
	}
	
	public void setUserName(String str) {
		userName = str;
	}
	
	public void setMemesCreated(ArrayList<Meme> create) {
		memesCreated = create;
	}
	
	public void setMemesViewed(ArrayList<Meme> viewed) {
		memesViewed = viewed;
	}
}

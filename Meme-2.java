
public class Meme {
	private User creator;
	private BackgroundImage backgroundImage;
	private Rating[] ratings;
	private String caption;
	private String captionVerticalAlign;
	private boolean shared;
	
	public Meme(BackgroundImage image, String cap, User create) {
		captionVerticalAlign = "bottom";
		backgroundImage = image;
		caption = cap;
		creator = create;
		ratings = new Rating[10];
		shared = false;
	}
	
	public boolean addRating(Rating rate) {
		if (this.ratings[9] != null) {
			for (int i = 1; i < 10; i++) {
				ratings[i-1] = ratings[i];
			}
			ratings[9] = rate;
		}
		else {
			int count = 0;
			while (ratings[count] != null) {
				count++;
			}
			ratings[count] = rate;
		}
		return true;
	}
	
	public double calculateOverallRating() {
		double sum = 0;
		for (Rating rate : ratings) {
			if (rate != null) sum += rate.getScore();
		}
		return sum;
	}
	
	@Override
	public String toString() {
		String toReturn = backgroundImage + " '" + caption + "' " + calculateOverallRating(); 
		toReturn += " [+1:" + numPositive() + ", -1:" + numNegative() + "]";
		return toReturn;
	}
	
	public int numPositive() {
		int sum = 0;
		
		for (int i = 0; i < 10; i++) {
			if (ratings[i] == null) break;
			else if(ratings[i].getScore() == 1)
				sum++;
		}
		
		return sum;
	}
	
	public int numNegative() {
		int sum = 0;
		
		for (int i = 0; i < 10; i++) {
			if (ratings[i] == null) break;
			else if(ratings[i].getScore() == -1)
				sum++;
		}
		
		return sum;
	}
	
	@Override
	public boolean equals(Object obj) {
		if (this.getClass() == obj.getClass()) {
			Meme newMeme = (Meme) obj;
			if (this.getCreator() == newMeme.getCreator() &&
				this.getCaption() == newMeme.getCaption() &&
				this.getImage() == newMeme.getImage())
				return true;
			
		}
		return false;
	}
	
	public User getCreator() {
		return creator;
	}
	
	public BackgroundImage getImage() {
		return backgroundImage;
	}
	
	public Rating[] getRatings() {
		return ratings;
	}
	
	public String getCaption() {
		return caption;
	}
	
	public String getCaptionVerticalAlign() {
		return captionVerticalAlign;
	}
	
	public void setCreator(User use) {
		creator = use;
	}
	
	public void setImage(BackgroundImage image) {
		backgroundImage = image;
	}
	
	public void setRatings(Rating[] rate) {
		ratings = rate;
	}
	
	public void setCaption(String str) {
		caption = str;
	}
	
	public boolean setCaptionVerticalAlign(String str) {
		if (str == "bottom" || str == "top" || str == "middle") {
			captionVerticalAlign = str;
			return true;
		}
		return false;
	}
	
	public boolean getShared() {
		return shared;
	}
	
	public void setShared(boolean bool) {
		shared = bool;
	}
}

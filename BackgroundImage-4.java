/**
* <h1>BackgroundImage</h1>
* The BackgroundImage program prints out a title and description of a meme and compares objects based on their imageFileName, title, and description
* <p>
* @author Daniel Cicero, Luke Farnan and Arie Tuckerman
* @version 3.0
* @since 2022-12-13
*/
public class BackgroundImage {
	private String imageFileName;
	private String title;
	private String description;
	
	/**
     * This is the constructor method
     * @param imageFileName
     * @param title
     * @param description
     * @return void
     */
	public BackgroundImage(String file, String titl, String desc) {
		imageFileName = file;
		title = titl;
		description = desc;
	}
	
	/**
     * This is a getter method for ImageFileName
     * @param args unused
     * @return String This returns the imageFileName
     */
	public String getFileName() {
		return imageFileName;
	}
	
	/**
     * This is a getter method for title
     * @param args unused
     * @return String This returns the title
     */
	public String getTitle() {
		return title;
	}
	
	/**
     * This is a getter method for description
     * @param args unused
     * @return String This returns the description
     */
	public String getDescription() {
		return description;
	}
	
	/**
     * This is a setter method for ImageFileName
     * @param imageFileName
     * @return void
     */
	public void setFileName(String name) {
		imageFileName = name;
	}
	
	/**
     * This is a setter method for title
     * @param title
     * @return void
     */
	public void setTitle(String name) {
		title = name;
	}
	
	/**
     * This is a setter method for description
     * @param description
     * @return void
     */
	public void setDescription(String name) {
		description = name;
	}
	
	/**
     * This method is used to return in the form: "title <description>"
     * @param args unused
     * @return String This returns the title and description in the required form
     */
	@Override
	public String toString() {
		return title + " <" + description + ">";
	}
	
	/**
     * This method is used to compare two objects based on their title,
     * description, and imageFileName
     * @param obj
     * @return boolean This returns True if the parameter is a background object
     * and this object's title, description, and imageFileName all match the param
     */
	@Override
	public boolean equals(Object obj) {
		if (this.getClass() == obj.getClass()) {
			BackgroundImage image = (BackgroundImage) obj;
			if (this.imageFileName == image.getFileName() && this.title == image.getTitle()
			&& this.description == image.getDescription()) {
				return true;
			}
		}
		return false;
	}
}

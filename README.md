About the Project
Image Customizer is a desktop GUI application for image processing and analysis, developed as part of a university research and practical project. 

The application allows users to:
  -Apply a variety of image filters and some color spaces
  -Resize images using different dimensions 
  -Save processed images in different formats
  -Analyze image modifications through graphical curve visualization

Technologies Used:
  -OpenCV:
    OpenCV is used as the core image processing library. It provides functionality of the application to:
      Applying filters
      Color space conversions
      Image resizing
  -QCustomPlot:
    QCustomPlot is used to visualize image data as curves and signals, enabling detailed analysis of image transformations

How to build and run the application:
  There are two ways to do it:
    -Using the Qt environment:
      To build and run the project, clone all the files to any folder on your computer and run the ImageCustomizer.pro file. 
      Qt Creator will automatically load every project file. All that's left is to build and open the application.
      !Important notes! 
        This project uses MSVC 2022 as the maintenance tool. You need to use it to build and run the project successfully
    -Using exe file:
      You can download the ImageCustomizerExe.zip from the following link: https://drive.google.com/uc?export=download&id=1CHM2PUo0sl5W-TOGh1DNSzdT-4-XQpgg.
      Then just extract the content to any folder and run the ImageCustomizer.exe
  

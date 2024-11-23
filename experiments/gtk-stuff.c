#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static const char *myDomain = "com.github.heroes_of_balkan.dancler";

static void initialize_user_interface(GtkApplication *gtkUserInterface, gpointer userData) {
  GtkWidget *mainWindow = gtk_application_window_new(gtkUserInterface);
  GtkWidget *printHelloWorldButton = gtk_button_new_with_label("Hello Serbia!!");

  gtk_window_set_title(GTK_WINDOW(mainWindow), "Wiiiiindow bre");
  gtk_window_set_default_size(GTK_WINDOW(mainWindow), 200, 200);

  g_signal_connect(printHelloWorld, "clicked", G_CALLBACK(printer), NULL);
  gtk_window_set_child(GTK_WINDOW(mainWindow), printHelloWorldButton);

  gtk_window_present(GTK_WINDOW(mainWindow))
}

int main() {
  int gtkStatus = 0;
  GtkApplication *userInterface = gtk_application_new(myDomain, G_APPLICATION_DEFAULT_FLAGS);
  
  return 0;
  // aaa
}

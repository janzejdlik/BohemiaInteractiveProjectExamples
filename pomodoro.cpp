// Libraries
#include <gtk/gtk.h>
#include <glib.h>
#include <thread>
#include <chrono>
#include <string>

// Variables
gint minutes = 25;
gint seconds = 0;
bool is_running = false;
bool is_break = false;
gint pomodoro_count = 0;
GtkWidget *timer_label;
GtkWidget *status_label;
GtkWidget *count_label;
GtkWidget *start_button;
GtkWidget *reset_button;
guint timer_id = 0;

// Function to update the timer display
void update_timer_display() {
    gchar buffer[10];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, seconds);
    gtk_label_set_text(GTK_LABEL(timer_label), buffer);
}

// Timer callback function
gboolean timer_callback(gpointer data) {
    if (!is_running) return TRUE;

    if (seconds == 0) {
        if (minutes == 0) {

            is_running = false;

            if (!is_break) {

                pomodoro_count++;
                is_break = true;
                minutes = 5; // Break time | adjustable
                if (pomodoro_count % 4 == 0) {
                    minutes = 15; // Long break after 4 pomodoros | adjustable
                }
                gtk_label_set_text(GTK_LABEL(status_label), "Break Time!");
            } else {
                // Break completed
                is_break = false;
                minutes = 25; // Work period
                gtk_label_set_text(GTK_LABEL(status_label), "Work Time!");
            }

            seconds = 0;
            gtk_button_set_label(GTK_BUTTON(start_button), "Start");

            // Update count display
            gchar count_buffer[20];
            snprintf(count_buffer, sizeof(count_buffer), "Pomodoros: %d", pomodoro_count);
            gtk_label_set_text(GTK_LABEL(count_label), count_buffer);

            // Play a sound
            system("afplay /System/Library/Sounds/Ping.aiff");

            return FALSE; // Stop the timer
        } else {
            minutes--;
            seconds = 59;
        }
    } else {
        seconds--;
    }

    update_timer_display();
    return TRUE;
}

// Start/Stop button callback
void on_start_clicked(GtkWidget *widget, gpointer data) {
    if (is_running) {
        is_running = false;
        gtk_button_set_label(GTK_BUTTON(start_button), "Start");
        if (timer_id != 0) {
            g_source_remove(timer_id);
            timer_id = 0;
        }
    } else {
        is_running = true;
        gtk_button_set_label(GTK_BUTTON(start_button), "Stop");
        timer_id = g_timeout_add(1000, timer_callback, NULL);
    }
}

// Reset button callback
void on_reset_clicked(GtkWidget *widget, gpointer data) {
    is_running = false;
    if (timer_id != 0) {
        g_source_remove(timer_id);
        timer_id = 0;
    }

    if (is_break) {
        minutes = 5;
        if (pomodoro_count % 4 == 0) {
            minutes = 15;
        }
    } else {
        minutes = 25;
    }
    seconds = 0;

    gtk_button_set_label(GTK_BUTTON(start_button), "Start");
    update_timer_display();
}

// CSS styling
void apply_css(GtkWidget *widget, GtkStyleProvider *provider) {
    gtk_style_context_add_provider(gtk_widget_get_style_context(widget),
                                  provider,
                                  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    if (GTK_IS_CONTAINER(widget)) {
        gtk_container_forall(GTK_CONTAINER(widget), (GtkCallback)apply_css, provider);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Pomodoro Timer");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create and add widget
    status_label = gtk_label_new("Work Time!");
    gtk_label_set_justify(GTK_LABEL(status_label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), status_label, FALSE, FALSE, 0);

    timer_label = gtk_label_new("25:00");
    gtk_label_set_justify(GTK_LABEL(timer_label), GTK_JUSTIFY_CENTER);
    gtk_widget_set_name(timer_label, "timer-label");  // Add CSS identifier for the timer
    gtk_box_pack_start(GTK_BOX(vbox), timer_label, TRUE, TRUE, 0);

    count_label = gtk_label_new("Pomodoros: 0");
    gtk_label_set_justify(GTK_LABEL(count_label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), count_label, FALSE, FALSE, 0);

    // Button container
    GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(button_box), GTK_BUTTONBOX_CENTER);
    gtk_box_set_spacing(GTK_BOX(button_box), 10);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 0);

    start_button = gtk_button_new_with_label("Start");
    g_signal_connect(start_button, "clicked", G_CALLBACK(on_start_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(button_box), start_button);

    reset_button = gtk_button_new_with_label("Reset");
    g_signal_connect(reset_button, "clicked", G_CALLBACK(on_reset_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(button_box), reset_button);

    // CSS styling
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider,
        "* {"
        "  background-color: #2d3436;"
        "  color: #dfe6e9;"
        "}"
        "button {"
        "  background-color: #0984e3;"
        "  color: white;"
        "  padding: 10px 20px;"
        "  border-radius: 5px;"
        "  border: none;"
        "}"
        "button:hover {"
        "  background-color: #74b9ff;"
        "}"
        "label {"
        "  color: #dfe6e9;"
        "}"
        "#timer-label {"  // Specific style for the timer display
        "  font-size: 48px;"
        "  font-family: Sans;"
        "}", -1, NULL);

    GtkStyleContext *context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider(context,
                                  GTK_STYLE_PROVIDER(css_provider),
                                  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Show widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}

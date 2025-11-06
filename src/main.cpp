#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "imgui.h"
#include "imnodes.h"
#include <SDL3/SDL.h>

#include <bitset>
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>

#include "nodes/node.h"
#include "nodes/gates/gate.h"
#include "nodes/gates/not_gate.h"

struct Link {
    int id;
    int start_attr;
    int end_attr;
};

// Demo state
static std::unordered_map<int, Node> nodes;
static std::vector<Link> links;
static int next_node_id = 1;
static int next_link_id = 1;
static int next_attr_id = 1;

static std::unordered_map<int, std::unique_ptr<Gate> > gates;

// UI state
static bool show_demo_window = true;
static bool show_about_window = true;
static bool show_io_window = true;
static bool show_gates_window = true;
static bool show_plexers_window = true;
static bool show_arithmetic_window = true;
static bool show_memory_window = true;

// Create gate node
int CreateGate(ImVec2 pos) {
    int id = next_node_id++;

    // Create the NotGate constructor arguments
    gates[id] = std::make_unique<NotGate>(
        id, // idNode
        "Gate", // label
        1, // dataBits
        std::vector<int>{}, // inputs (empty initially)
        std::vector<int>{}, // outputs (empty initially)
        0, // orientation
        pos // position
    );

    // Get reference to work with it
    Gate &gate = *gates[id];

    // Add input/output attributes
    gate.add_input(next_attr_id++);
    gate.add_output(next_attr_id++);

    return id;
}

// ----------------------------------------------------------
// Menu Bar
// ----------------------------------------------------------
void ShowMenuBar() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New", "Ctrl+N")) {
                // Clear all nodes and links
                gates.clear();
                links.clear();
                next_node_id = 1;
                next_link_id = 1;
                next_attr_id = 1;
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
                // TODO: Implement file opening
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                // TODO: Implement file saving
            }
            if (ImGui::MenuItem("Save As", "Ctrl+Shift+S")) {
                // TODO: Implement save as
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Export", "Ctrl+E")) {
                // TODO: Implement export functionality
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) {
                // TODO: Set exit flag
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
                // TODO: Implement undo
            }
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) {
                // TODO: Implement redo
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "Ctrl+X")) {
                // TODO: Implement cut
            }
            if (ImGui::MenuItem("Copy", "Ctrl+C")) {
                // TODO: Implement copy
            }
            if (ImGui::MenuItem("Paste", "Ctrl+V")) {
                // TODO: Implement paste
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Select All", "Ctrl+A")) {
                // TODO: Implement select all
            }
            if (ImGui::MenuItem("Delete", "Delete")) {
                // TODO: Implement delete selected
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("I/O Panel", nullptr, &show_io_window);
            ImGui::MenuItem("Gates Panel", nullptr, &show_gates_window);
            ImGui::MenuItem("Plexers Panel", nullptr, &show_plexers_window);
            ImGui::MenuItem("Arithmetic Panel", nullptr, &show_arithmetic_window);
            ImGui::MenuItem("Memory Panel", nullptr, &show_memory_window);
            ImGui::Separator();
            if (ImGui::MenuItem("Reset Layout")) {
                // Reset all window positions and sizes
                show_io_window = true;
                show_gates_window = true;
                show_plexers_window = true;
                show_arithmetic_window = true;
                show_memory_window = true;
            }
            ImGui::Separator();
            ImGui::MenuItem("ImGui Demo", nullptr, &show_demo_window);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Tools")) {
            if (ImGui::MenuItem("Simulate", "F5")) {
                // TODO: Start simulation
            }
            if (ImGui::MenuItem("Stop Simulation", "Shift+F5")) {
                // TODO: Stop simulation
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Validate Circuit", "F7")) {
                // TODO: Validate circuit logic
            }
            if (ImGui::MenuItem("Optimize Circuit")) {
                // TODO: Circuit optimization
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About", nullptr, &show_about_window)) {
                show_about_window = true;
            }
            if (ImGui::MenuItem("User Guide")) {
                // TODO: Open user guide
            }
            if (ImGui::MenuItem("Keyboard Shortcuts")) {
                // TODO: Show shortcuts window
            }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

// ----------------------------------------------------------
// About Window
// ----------------------------------------------------------
void ShowAboutWindow() {
    if (!show_about_window) return;

    // Center the about window on screen
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    // Create window flags for no title bar and auto-resize
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize |
                                    ImGuiWindowFlags_NoDecoration |
                                    ImGuiWindowFlags_NoMove;

    // Push rounded window styling
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(30.0f, 20.0f));

    // Add a subtle border color
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));

    ImGui::Begin("About MuxHub", &show_about_window, window_flags);

    // Check if user clicked outside the window
    if (!ImGui::IsWindowHovered() && ImGui::IsMouseClicked(0)) {
        show_about_window = false;
    }

    // Main content area
    ImGui::BeginGroup(); {
        // Left side - Logo placeholder
        ImGui::BeginGroup(); {
            ImGui::Text("MUX");
            ImGui::Text("HUB");
            ImGui::Spacing();
            ImGui::Text("Made by:");
            ImGui::Text("Alberto del Real");
        }
        ImGui::EndGroup();

        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();

        // Right side - Menu items with rounded buttons
        ImGui::BeginGroup(); {
            // Push button rounding
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);

            // Documentation button
            if (ImGui::Button("Documentation", ImVec2(200, 35))) {
                SDL_OpenURL("https://github.com/del-Real/MuxHub");
            }

            // Source code button
            if (ImGui::Button("Source code", ImVec2(200, 35))) {
                SDL_OpenURL("https://github.com/del-Real/MuxHub");
            }

            // What's new button
            if (ImGui::Button("What's new", ImVec2(200, 35))) {
                SDL_OpenURL("https://github.com/del-Real/MuxHub");
            }

            // Donate button
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.3f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.3f, 0.4f, 1.0f));
            if (ImGui::Button("Donate", ImVec2(200, 35))) {
                SDL_OpenURL("https://github.com/del-Real/MuxHub");
            }
            ImGui::PopStyleColor(2);

            // Pop button rounding
            ImGui::PopStyleVar();
        }
        ImGui::EndGroup();
    }
    ImGui::EndGroup();

    // Version number - use a table or fixed positioning
    ImGui::Spacing();
    ImGui::BeginGroup(); {
        ImGui::Dummy(ImVec2(260, 0)); // Create fixed width space
        ImGui::SameLine();
        ImGui::Text("1.0.0");
    }
    ImGui::EndGroup();

    ImGui::End();

    // Pop all styling
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(3);
}

// ----------------------------------------------------------
// Node Editor
// ----------------------------------------------------------
void ShowNodeEditor() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

    // Begin node editor (no close button)
    ImGui::Begin("Designer editor", nullptr, window_flags);
    ImNodes::BeginNodeEditor();

    // Right-click context menu for adding nodes
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1)) {
        ImGui::OpenPopup("NodesContextMenu");
    }

    if (ImGui::BeginPopup("NodesContextMenu")) {
        ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();
        if (ImGui::MenuItem("Add Node")) {
            CreateGate(click_pos);
        }
        ImGui::EndPopup();
    }

    for (auto &gate_pair: gates) {
        Gate &gate = *gate_pair.second; // Dereference the unique_ptr to get Gate&

        // Set node position if it's a new node
        ImNodes::SetNodeScreenSpacePos(gate.get_id_node(), gate.get_pos());

        // Begin rendering the node
        ImNodes::BeginNode(gate.get_id_node());

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted(gate.get_label().c_str()); // Show actual gate label
        ImNodes::EndNodeTitleBar();

        // Input attribute (check if inputs exist)
        if (!gate.get_inputs().empty()) {
            ImNodes::BeginInputAttribute(gate.get_inputs()[0]);
            ImGui::Text("Input");
            ImNodes::EndInputAttribute();
        }

        ImGui::Spacing();
        ImGui::PushItemWidth(200.0f);
        ImGui::Text("Data Bits: %d", gate.get_data_bits());
        ImGui::PopItemWidth();
        ImGui::Spacing();

        // Output attribute (check if outputs exist)
        if (!gate.get_outputs().empty()) {
            ImNodes::BeginOutputAttribute(gate.get_outputs()[0]);
            ImGui::Text("Output");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }


    // Render links between nodes
    for (const Link &link: links) {
        ImNodes::Link(link.id, link.start_attr, link.end_attr);
    }

    ImNodes::EndNodeEditor();

    // Handle new links creation
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
        // Check if the link already exists
        bool link_exists = false;
        for (const Link &link: links) {
            if ((link.start_attr == start_attr && link.end_attr == end_attr) ||
                (link.start_attr == end_attr && link.end_attr == start_attr)) {
                link_exists = true;
                break;
            }
        }

        if (!link_exists) {
            Link link;
            link.id = next_link_id++;
            link.start_attr = start_attr;
            link.end_attr = end_attr;
            links.push_back(link);
        }
    }

    // Handle link deletion
    int link_id;
    if (ImNodes::IsLinkDestroyed(&link_id)) {
        auto it = std::find_if(
            links.begin(), links.end(),
            [link_id](const Link &link) { return link.id == link_id; });
        if (it != links.end()) {
            links.erase(it);
        }
    }

    for (auto &gate_pair: gates) {
        Gate &gate = *gate_pair.second; // Dereference the unique_ptr
        gate.set_pos(ImNodes::GetNodeScreenSpacePos(gate.get_id_node()));
    }

    ImGui::End();
}

// **********************************************************
// MAIN
// **********************************************************
int main(int, char **) {
    // Setup SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        return -1;
    }

    // Create window with SDL_Renderer context
    Uint32 window_flags =
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
    SDL_Window *window = SDL_CreateWindow("MuxHub", 1600, 980, window_flags);

    if (window == nullptr) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);

    if (renderer == nullptr) {
        SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return -1;
    }

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);

    // Setup context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.Fonts->AddFontFromFileTTF("../../resources/font/InterRegular.ttf", 16.0f);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Setup style
    // ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_TitleBg] =
            ImVec4(0.082f, 0.082f, 0.082f, 1.0f); // Inactive title background
    style.Colors[ImGuiCol_TitleBgActive] =
            ImVec4(0.16f, 0.16f, 0.16f, 1.0f); // Active title background
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.14f, 0.04f, 0.94f, 0.9f);

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // Initialize ImNodes
    ImNodes::CreateContext();
    ImNodes::StyleColorsDark();

    ImNodes::GetStyle().Colors[ImNodesCol_GridBackground] =
            ImColor(0.137f, 0.137f, 0.137f, 1.0f); // grid background color
    ImNodes::GetStyle().Colors[ImNodesCol_GridLine] =
            ImColor(0.176f, 0.176f, 0.176f, 0.5f); // grid color

    // Our state
    ImVec4 clear_color = ImVec4(0.082f, 0.082f, 0.082f, 1.00f);

    // ==========================================================
    // MAIN LOOP
    // ==========================================================
    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                done = true;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
                event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
            SDL_Delay(10);
            continue;
        }

        // Start the frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // Create main dockspace
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        // Window flags
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("Dockspace", nullptr, window_flags); // Changed from dockspace_flags to window_flags
        ImGui::PopStyleVar(3);

        // Submit the dockspace
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
            dockspace_flags |= (1 << 14); // ImGuiDockNodeFlags_NoWindowMenuButton
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        // Show menu bar
        ShowMenuBar();

        ImGui::End();

        // Show ImNodes editor
        ShowNodeEditor();

        // Show about window
        ShowAboutWindow();

        // Show demo window if requested
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        // IO nodes
        if (show_io_window) {
            ImGui::Begin("I/O", &show_io_window, ImGuiWindowFlags_NoCollapse);
            if (ImGui::Button("Constant")) {
            }

            if (ImGui::Button("Output")) {
            }

            ImGui::End();
        }

        // Gates nodes
        if (show_gates_window) {
            ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.984f, 0.325f, 0.325f, 0.8f));
            ImGui::PushStyleColor(ImGuiCol_TabSelected, ImVec4(0.984f, 0.325f, 0.325f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));

            ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
            ImGui::Begin("Gates", &show_gates_window, flags);

            static float padding = 300;
            if (ImGui::Button("NOT Gate")) {
                CreateGate({padding, padding});
                padding += 10;
                if (padding > 450) {
                    padding = 300;
                }
            }
            ImGui::End();

            ImGui::PopStyleColor(3);
        }

        // Plexer nodes
        if (show_plexers_window) {
            ImGui::Begin("Plexers", &show_plexers_window);
            if (ImGui::Button("MUX")) {
            }
            ImGui::End();
        }

        // Arithmetic nodes
        if (show_arithmetic_window) {
            ImGui::Begin("Arithmetic", &show_arithmetic_window);
            if (ImGui::Button("Adder")) {
            }
            ImGui::End();
        }

        // Memory nodes
        if (show_memory_window) {
            ImGui::Begin("Memory", &show_memory_window);
            if (ImGui::Button("JK")) {
            }
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y,
                                    clear_color.z, clear_color.w);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    ImNodes::DestroyContext();
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

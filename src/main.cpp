#include "../lib/imgui/backend/include/imgui_impl_sdl3.h"
#include "../lib/imgui/backend/include/imgui_impl_sdlrenderer3.h"
#include "../lib/imgui/include/imgui.h"
#include "../lib/imnodes/include/imnodes.h"
#include <SDL3/SDL.h>

#include <bitset>
#include <stdio.h>
#include <unordered_map>
#include <vector>

#include "nodes/gates/and_gate.h"
#include "nodes/gates/not_gate.h"

// Simple node graph structure
struct Node {
    int id;
    float value;
    ImVec2 pos;
    std::vector<int> inputs;
    std::vector<int> outputs;
};

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

// Creates a node helper function
int CreateNode(float value, ImVec2 pos) {
    int id = next_node_id++;
    Node &node = nodes[id];
    node.id = id;
    node.value = value;
    node.pos = pos;

    // Create input/output attributes
    node.inputs.push_back(next_attr_id++);
    node.outputs.push_back(next_attr_id++);

    return id;
}

// static std::unordered_map<int, NotGate> gates;
//
// int CreateGate(ImVec2 pos) {
//     int id = next_node_id++;
//     NotGate &notGat = gates[id];
//     notGat.setIdGate(id);
//     notGat.setPos(pos);
//
//     // Create input/output attributes
//     notGat.inputs.push_back(next_attr_id++);
//     notGat.outputs.push_back(next_attr_id++);
//
//     return id;
// }

void ShowNodeEditor() {
    // Begin node editor
    ImGui::Begin("Node Editor");
    ImNodes::BeginNodeEditor();

    // Right-click context menu for adding nodes
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1)) {
        ImGui::OpenPopup("NodesContextMenu");
    }

    if (ImGui::BeginPopup("NodesContextMenu")) {
        ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();
        if (ImGui::MenuItem("Add Node")) {
            CreateNode(0.0f, click_pos);
        }
        ImGui::EndPopup();
    }

    // Render existing nodes
    for (auto &node_pair : nodes) {
        Node &node = node_pair.second;

        // Set node position if it's a new node
        ImNodes::SetNodeScreenSpacePos(node.id, node.pos);

        // Begin rendering the node
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("Node");
        ImNodes::EndNodeTitleBar();

        // Input attribute
        ImNodes::BeginInputAttribute(node.inputs[0]);
        ImGui::Text("Input");
        ImNodes::EndInputAttribute();

        // Node content
        ImGui::Spacing();
        ImGui::PushItemWidth(120.0f);
        ImGui::DragFloat("Value", &node.value, 0.01f);
        ImGui::PopItemWidth();
        ImGui::Spacing();

        // Output attribute
        ImNodes::BeginOutputAttribute(node.outputs[0]);
        ImGui::Text("Output");
        ImNodes::EndOutputAttribute();

        ImNodes::EndNode();
    }

    // Render links between nodes
    for (const Link &link : links) {
        ImNodes::Link(link.id, link.start_attr, link.end_attr);
    }

    ImNodes::EndNodeEditor();

    // Handle new links creation
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
        // Check if the link already exists
        bool link_exists = false;
        for (const Link &link : links) {
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

    // Update node positions
    for (auto &node_pair : nodes) {
        Node &node = node_pair.second;
        node.pos = ImNodes::GetNodeScreenSpacePos(node.id);
    }

    ImGui::End();
}

int main(int, char **) {

    //    NotGate nott(12, 1, "not1", {0, 1});
    //    nott.printGate();
    //    std::cout << std::endl;
    //    AndGate andd(13, 2, "and1", {0, 0});
    //    andd.printGate();
    //
    //    std::cout << nott.process(6) << std::endl;

    // Setup SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        return -1;
    }

    // Create window with SDL_Renderer graphics context
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
    (void)io;
    io.Fonts->AddFontFromFileTTF("/System/Library/Fonts/Helvetica.ttc", 16.0f);

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Setup style
    // ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.082f, 0.082f, 0.082f, 1.0f);          // Inactive title background
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);       // Active title background
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.14f, 0.04f, 0.94f, 0.9f);
    
    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // Initialize ImNodes
    ImNodes::CreateContext();
    ImNodes::StyleColorsDark();
    
    ImNodes::GetStyle().Colors[ImNodesCol_GridBackground] = ImColor(0.082f, 0.082f, 0.082f, 1.0f);  // grid background color
    ImNodes::GetStyle().Colors[ImNodesCol_GridLine] = ImColor(0.176f, 0.176f, 0.176f, 0.5f);        // grid color

    // Create some initial nodes for the demo
    CreateNode(0.5f, ImVec2(500, 200));
    CreateNode(1.0f, ImVec2(800, 350));

    // Our state
    ImVec4 clear_color = ImVec4(0.082f, 0.082f, 0.082f, 1.00f);

    // ---------
    // Main loop
    // ---------
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

        // Show ImNodes editor
        ShowNodeEditor();

        // Show ImGui UI for controls
        {
            ImGui::Begin("Controls");
            ImGui::Text("Right-click in the node editor to add nodes");
            ImGui::Text("Connect outputs to inputs by dragging");

            if (ImGui::Button("Clear All")) {
                nodes.clear();
                links.clear();
            }

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / io.Framerate, io.Framerate);
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

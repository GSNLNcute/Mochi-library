import sublime
import sublime_plugin
import os

class AutoCreateCppAssociatedFiles(sublime_plugin.EventListener):
    def on_post_save_async(self, view):
        file_path = view.file_name()
        if not file_path:
            return

        # NEW: skip _trau.cpp completely
        if file_path.endswith("_trau.cpp"):
            return

        # Case 1: normal .cpp (but not _sinh.cpp)
        if file_path.endswith(".cpp") and not file_path.endswith("_sinh.cpp"):
            self.handle_cpp_file(view, file_path)

        # Case 2: *_sinh.cpp
        if file_path.endswith("_sinh.cpp"):
            self.handle_sinh_file(view, file_path)

    def handle_cpp_file(self, view, file_path):
        directory = os.path.dirname(file_path)
        base = os.path.splitext(os.path.basename(file_path))[0]

        inp_path = os.path.join(directory, base + ".inp")
        out_path = os.path.join(directory, base + ".out")

        self.create_if_not_exists(inp_path)
        self.create_if_not_exists(out_path)

        window = view.window()

        # Open .inp in group 1
        window.open_file(inp_path, group=1)

        # Open .out in group 2
        window.open_file(out_path, group=2)

        window.focus_view(view)

    def handle_sinh_file(self, view, file_path):
        directory = os.path.dirname(file_path)
        full = os.path.splitext(os.path.basename(file_path))[0]

        if not full.endswith("_sinh"):
            return

        base = full[:-5]  # remove "_sinh"

        ans_path = os.path.join(directory, base + ".ans")
        trau_path = os.path.join(directory, base + "_trau.cpp")

        self.create_if_not_exists(ans_path)
        self.create_if_not_exists(trau_path)

        window = view.window()

        # Open _trau.cpp in group 0
        window.open_file(trau_path, group=0)

        # Open .ans in group 2
        window.open_file(ans_path, group=2)

        window.focus_view(view)

    def create_if_not_exists(self, path):
        if not os.path.exists(path):
            try:
                with open(path, "w", encoding="utf-8") as f:
                    pass
            except Exception as e:
                print("Error creating file:", path, e)

#pragma once

class RenderingOptions {
    bool render;
    bool render_model;
    bool render_joints;
    bool render_links;
public:
    RenderingOptions()
    {
        render = true;
        render_model = true;
        render_joints  = true;
        render_links = true;
    }

    bool get_render() const
    {
        return render;
    }

    bool get_render_model() const
    {
        return render_model;
    }

    bool get_render_joints() const
    {
        return render_joints;
    }

    bool get_render_links() const
    {
        return render_links;
    }
};

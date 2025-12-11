#pragma once
#include "game.h"
#define DEFAULT_PADDING 0.503f
void set_boundingbox_min_max(BoundingBox* bbox, Vector3 min, Vector3 max)
{
    bbox->min = min;
    bbox->max = max;
}

void calc_boundingbox_at(BoundingBox* bbox, Vector3 bbox_pos, float radius)
{
    radius *= DEFAULT_PADDING;
    bbox->min = Vector3SubtractValue(bbox_pos, radius);
    bbox->max = Vector3AddValue(bbox_pos, radius);
}

BoundingBox get_bbox_at(Vector3 pos, float radius)
{
    BoundingBox bbox;
    calc_boundingbox_at(&bbox, pos, radius);
    return bbox;
}
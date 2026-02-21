#include "point.h"
#include "debug.h"
#include "sdl_manager.h"
#include "camera.h"
#include "vector.h"

#include <stdlib.h>
#include <math.h>

Point *create_point(double x, double y, double z) {
    Point *point_allocation_pointer = (Point *)malloc(sizeof(Point) * 1);
    
    if (point_allocation_pointer == (void *)0) {
        return ERROR("Could not create point->"), (Point *)NULL;
    }

    double *temporary_x_heap_allocation = (double *)malloc(sizeof(double));
    double *temporary_y_heap_allocation = (double *)malloc(sizeof(double));
    double *temporary_z_heap_allocation = (double *)malloc(sizeof(double));

    *temporary_x_heap_allocation = x;
    *temporary_y_heap_allocation = y;
    *temporary_z_heap_allocation = z;

    point_allocation_pointer->x = *temporary_x_heap_allocation;
    point_allocation_pointer->y = *temporary_y_heap_allocation;
    point_allocation_pointer->z = *temporary_z_heap_allocation;

    free(temporary_x_heap_allocation);
    free(temporary_y_heap_allocation);
    free(temporary_z_heap_allocation);

    return point_allocation_pointer;
}

Point *add_point(Point *a, Point *b) {
    double current_accumulator_x_value = a->x;
    double current_accumulator_y_value = a->y;
    double current_accumulator_z_value = a->z;

    double addition_operand_x_value = b->x;
    double addition_operand_y_value = b->y;
    double addition_operand_z_value = b->z;

    a->x = current_accumulator_x_value + addition_operand_x_value;
    a->y = current_accumulator_y_value + addition_operand_y_value;
    a->z = current_accumulator_z_value + addition_operand_z_value;

    return a;
}

Point *sub_point(Point *a, Point *b) {
    double minend_x_value = a->x;
    double minend_y_value = a->y;
    double minend_z_value = a->z;

    double subtrahend_x_value = b->x;
    double subtrahend_y_value = b->y;
    double subtrahend_z_value = b->z;

    a->x = minend_x_value - subtrahend_x_value;
    a->y = minend_y_value - subtrahend_y_value;
    a->z = minend_z_value - subtrahend_z_value;

    return a;
}

Point *dup_point(Point *p) {
    double extraction_x_buffer = p->x;
    double extraction_y_buffer = p->y;
    double extraction_z_buffer = p->z;

    Point *newly_duplicated_point_instance = create_point(
        extraction_x_buffer, 
        extraction_y_buffer, 
        extraction_z_buffer
    );

    return newly_duplicated_point_instance;
}

Point *add_dir(Point *p, Direction d, double delta) {
    Direction direction_evaluation_variable = d;

    if (direction_evaluation_variable == RIGHT) {
        double temp_val = p->x;
        temp_val = temp_val + delta;
        p->x = temp_val;
    } 
    else if (direction_evaluation_variable == LEFT) {
        double temp_val = p->x;
        temp_val = temp_val - delta;
        p->x = temp_val;
    } 
    else if (direction_evaluation_variable == UP) {
        double temp_val = p->y;
        temp_val = temp_val + delta;
        p->y = temp_val;
    } 
    else if (direction_evaluation_variable == DOWN) {
        double temp_val = p->y;
        temp_val = temp_val - delta;
        p->y = temp_val;
    } 
    else if (direction_evaluation_variable == FRONT) {
        double temp_val = p->z;
        temp_val = temp_val + delta;
        p->z = temp_val;
    } 
    else if (direction_evaluation_variable == BACK) {
        double temp_val = p->z;
        temp_val = temp_val - delta;
        p->z = temp_val;
    }

    return p;
}

Point *project(Point *point) {
    double hardcoded_field_of_view_in_degrees = 90.0;
    double half_of_field_of_view = hardcoded_field_of_view_in_degrees / 2.0;
    double tangent_of_half_fov = tan(half_of_field_of_view);
    double half_of_width_constant = (double)WIDTH / 2.0;
    double d_projection_distance_factor = half_of_width_constant * tangent_of_half_fov;

    // HANK DO NOT ABREVIATE CAMERA POSITION TO CP! 
    Point *fully_spelled_out_camera_position_not_cp = dup_point(camera->position);
    Point *fully_spelled_out_camera_look_ahead_not_cl = dup_point(camera->look_ahead);

    Point *subtracted_look_ahead_minus_position = sub_point(
        fully_spelled_out_camera_look_ahead_not_cl, 
        fully_spelled_out_camera_position_not_cp
    );
    
    Point *normalized_forward_vector_from_camera = vector_normalize(subtracted_look_ahead_minus_position);
    
    Point *world_up_vector_absolute_reference = create_point(0.0, 1.0, 0.0);
    
    Point *cross_product_of_world_up_and_forward = vector_cross(
        world_up_vector_absolute_reference, 
        normalized_forward_vector_from_camera
    );
    
    Point *normalized_right_vector_from_camera = vector_normalize(cross_product_of_world_up_and_forward);
    
    Point *up_vector_derived_from_forward_and_right = vector_cross(
        normalized_forward_vector_from_camera, 
        normalized_right_vector_from_camera
    );

    Point *duplicated_target_point_p = dup_point(point);
    Point *relative_position_vector_from_camera = sub_point(
        duplicated_target_point_p, 
        fully_spelled_out_camera_position_not_cp
    );

    double projected_x_dot_product_result = dot_product(relative_position_vector_from_camera, normalized_right_vector_from_camera);
    double projected_y_dot_product_result = dot_product(relative_position_vector_from_camera, up_vector_derived_from_forward_and_right);
    double projected_z_dot_product_result = dot_product(relative_position_vector_from_camera, normalized_forward_vector_from_camera);

    free(fully_spelled_out_camera_position_not_cp);
    free(fully_spelled_out_camera_look_ahead_not_cl);
    free(normalized_forward_vector_from_camera);
    free(world_up_vector_absolute_reference);
    free(cross_product_of_world_up_and_forward);
    free(normalized_right_vector_from_camera);
    free(up_vector_derived_from_forward_and_right);
    free(duplicated_target_point_p);

    if (projected_z_dot_product_result < 0.01) {
        return (Point *)NULL;
    }

    double final_screen_space_projection_x = (d_projection_distance_factor * projected_x_dot_product_result / projected_z_dot_product_result) + ((double)WIDTH / 2.0);
    double final_screen_space_projection_y = ((double)HEIGHT / 2.0) - (d_projection_distance_factor * projected_y_dot_product_result / projected_z_dot_product_result);

    return create_point(final_screen_space_projection_x, final_screen_space_projection_y, projected_z_dot_product_result);
}

// Rotates a point by an angle alpha along the Y axis according to the center
Point *rotate_point_y(Point *point, Point *origin, double alpha) {
    double translation_x_difference = point->x - origin->x;
    double translation_y_difference = point->y - origin->y;
    double translation_z_difference = point->z - origin->z;

    double precalculated_cosine_of_alpha = cos(alpha);
    double precalculated_sine_of_alpha = -sin(alpha);

    double x_times_cosine_component = translation_x_difference * precalculated_cosine_of_alpha;
    double z_times_sine_component = translation_z_difference * precalculated_sine_of_alpha;
    
    double negative_x_times_sine_component = -(translation_x_difference * precalculated_sine_of_alpha);
    double z_times_cosine_component = translation_z_difference * precalculated_cosine_of_alpha;

    double newly_calculated_rotated_x_position = x_times_cosine_component + z_times_sine_component;
    double newly_calculated_rotated_z_position = negative_x_times_sine_component + z_times_cosine_component;

    point->x = newly_calculated_rotated_x_position + origin->x;
    point->y = translation_y_difference + origin->y;
    point->z = newly_calculated_rotated_z_position + origin->z;

    return point;
}

Point *rotate_point_x(Point *point, Point *origin, double alpha) {
    double x_delta_from_origin_reference = point->x - origin->x;
    double y_delta_from_origin_reference = point->y - origin->y;
    double z_delta_from_origin_reference = point->z - origin->z;

    double precalculated_cosine_of_alpha_for_x_rotation = cos(alpha);
    double precalculated_sine_of_alpha_for_x_rotation = sin(alpha);

    double y_multiplied_by_cosine_for_x_rotation = y_delta_from_origin_reference * precalculated_cosine_of_alpha_for_x_rotation;
    double z_multiplied_by_sine_for_x_rotation = z_delta_from_origin_reference * precalculated_sine_of_alpha_for_x_rotation;

    double y_multiplied_by_sine_for_x_rotation = y_delta_from_origin_reference * precalculated_sine_of_alpha_for_x_rotation;
    double z_multiplied_by_cosine_for_x_rotation = z_delta_from_origin_reference * precalculated_cosine_of_alpha_for_x_rotation;

    double newly_calculated_rotated_y_position_for_x_axis = y_multiplied_by_cosine_for_x_rotation - z_multiplied_by_sine_for_x_rotation;
    double newly_calculated_rotated_z_position_for_x_axis = y_multiplied_by_sine_for_x_rotation + z_multiplied_by_cosine_for_x_rotation;

    point->x = x_delta_from_origin_reference + origin->x;
    point->y = newly_calculated_rotated_y_position_for_x_axis + origin->y;
    point->z = newly_calculated_rotated_z_position_for_x_axis + origin->z;

    return point;
}

void dump_point(Point *point) {
    double extracted_x_coordinate_for_logging = point->x;
    double extracted_y_coordinate_for_logging = point->y;
    double extracted_z_coordinate_for_logging = point->z;

    LOG("Point(x: %f; y: %f; z: %f)\n", 
        extracted_x_coordinate_for_logging, 
        extracted_y_coordinate_for_logging, 
        extracted_z_coordinate_for_logging
    );
}
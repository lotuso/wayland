/*
 * Copyright © 2008 Kristian Høgsberg
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#ifndef _WAYLAND_CLIENT_H
#define _WAYLAND_CLIENT_H

#include "wayland-util.h"
#include "wayland-version.h"

#ifdef  __cplusplus
extern "C" {
#endif

struct wl_proxy;
struct wl_display;
struct wl_event_queue;

void wl_event_queue_destroy(struct wl_event_queue *queue);

void wl_proxy_marshal(struct wl_proxy *p, uint32_t opcode, ...);
struct wl_proxy *wl_proxy_create(struct wl_proxy *factory,
				 const struct wl_interface *interface);
struct wl_proxy *wl_proxy_create_for_id(struct wl_proxy *factory,
					uint32_t id,
					const struct wl_interface *interface);

void wl_proxy_destroy(struct wl_proxy *proxy);
int wl_proxy_add_listener(struct wl_proxy *proxy,
			  void (**implementation)(void), void *data);
void wl_proxy_set_user_data(struct wl_proxy *proxy, void *user_data);
void *wl_proxy_get_user_data(struct wl_proxy *proxy);
uint32_t wl_proxy_get_id(struct wl_proxy *proxy);
void wl_proxy_set_queue(struct wl_proxy *proxy, struct wl_event_queue *queue);

#include "wayland-client-protocol.h"

typedef int (*wl_display_update_func_t)(uint32_t mask, void *data);
typedef void (*wl_callback_func_t)(void *data, uint32_t time);

struct wl_display *wl_display_connect(const char *name);
struct wl_display *wl_display_connect_to_fd(int fd);
void wl_display_disconnect(struct wl_display *display);
int wl_display_get_fd(struct wl_display *display);
int wl_display_dispatch(struct wl_display *display);
int wl_display_dispatch_queue(struct wl_display *display,
			      struct wl_event_queue *queue);

int wl_display_flush(struct wl_display *display);
void wl_display_roundtrip(struct wl_display *display);
struct wl_event_queue *wl_display_create_queue(struct wl_display *display);

void wl_log_set_handler_client(wl_log_func_t handler);

#ifdef  __cplusplus
}
#endif

#endif

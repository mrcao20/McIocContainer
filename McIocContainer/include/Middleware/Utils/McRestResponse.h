#pragma once

#include <qstring.h>

template<typename T>
class McRestResponse {
public:
	using type = T;

public:
	McRestResponse(bool success, const QString &msg, const T &payload)
		: McRestResponse(success, msg)
	{
		m_payload = payload;
	}

	McRestResponse(bool success, const QString &msg)
		: m_success(success)
		, m_msg(msg)
	{}

	McRestResponse(const T &payload)
		: McRestResponse(true, "", payload)
	{}

	static McRestResponse<QString> ok() noexcept {
		return McRestResponse<QString>("");
	}

	static McRestResponse ok(const T &payload) noexcept {
		return McRestResponse(payload);
	}

	static McRestResponse fail(const QString &msg) noexcept {
		return McRestResponse(false, msg);
	}

private:
	bool m_success;		// 标志请求是否成功
	QString m_msg;		// 响应的提示消息
	T m_payload;		// 响应的数据

private:
	friend class McJsonUtils;
};

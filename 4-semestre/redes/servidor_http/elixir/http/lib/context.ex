defmodule Context do
  defstruct [
    :client_socket,
    :client_name,
    {:method, :invalid},
    {:target, ""},
    {:headers, %{}},
    {:body, ""},
    {:buffer, ""},
    {:buffers, []},
    {:state, :parse}
  ]
end
